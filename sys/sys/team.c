#include <ansi.h>
#include <equip.h>
#include <skill.h>

inherit DBASE_F;
#define TEAM_DATA "npc/std/team"

static int iCall; //是否有callout
private
static int team_id; //队伍ID，累加
private
static int group_id; //团队ID，累加
private
mapping mpTeam = ([]); //以队长ID对应存放队伍ID
private
static mapping mpItem = ([]);
private
mapping mpGroup = ([]); //团队的有关信息，以团队ID为KEY
mapping mpGainMode = ([0:"Tự do", 1:"Đội trưởng phân phối", 2:"Phân phối theo nhóm", 3:"Luân phiên nhặt đồ", 4:"Phân phối theo nhu cầu", ]);
int add_member(string id, object who);
int change_leader(object leader, object who);
void check_bonus_task(string id);
void distribute_item_call();
int check_equip(object who, object item);
void dest_copy_scene(int tId);
int remove_group_team(int tId);

// 函数:生成二进制码
void SAVE_BINARY() {}

// 函数:构造处理
void create()
{
	int i, size;
	string *nKey;
	mapping mpTmp;

	call_out("distribute_item_call", 1);
	team_id = TEAM_DATA->get_2("team_id");
	if (!team_id)
		return;
	mpTmp = TEAM_DATA->get_2("mpTeam");
	if (mapp(mpTmp))
		mpTeam = mpTmp;
	mpTmp = TEAM_DATA->get_2("mpGroup");
	if (mapp(mpTmp))
		mpGroup = mpTmp;
	mpItem = TEAM_DATA->get_2("items");
	if (!mapp(mpItem))
		mpItem = ([]);
	mpTmp = TEAM_DATA->get_2("database");
	if (!mapp(mpTmp))
		return;
	nKey = keys(mpTmp);
	for (i = 0, size = sizeof(nKey); i < size; i++)
	{
		set_save_2(nKey[i], mpTmp[nKey[i]]);
	}
}

// 函数:获取队伍ID数组
mapping get_all_teams() { return copy(mpTeam); }

// 函数:获取队伍成员数组
object *get_team(string id)
{
	int tId;
	object *nObj;
	if (undefinedp(tId = mpTeam[id]) || tId == 0)
		return 0;
	nObj = get_save_2(sprintf("%d.member", tId));
	if (sizeof(nObj))
		return copy(nObj);
	return 0;
}

object *get_team_by_id(int tId)
{
	object *nObj;
	if (tId == 0)
		return 0;
	nObj = get_save_2(sprintf("%d.member", tId));
	if (sizeof(nObj))
		return copy(nObj);
	return 0;
}
//新建一支队伍
int new_team(object who)
{
	string id;
	if (!who || !who->is_user())
		return 0;
	if (who->get_team_id())
		return 0;
	team_id++;
	if (team_id < 0)
		return 0;
	id = sprintf("%d", who->get_number());
	mpTeam[id] = team_id;
	set_save_2(sprintf("%d.leader", team_id), id); //以队伍ID记录队伍的相关信息
	set_save_2(sprintf("%d.member", team_id), ({who}));
	who->set_team_id(team_id);
	send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 9111, 1, OVER_BODY, PF_LOOP);
	return 1;
}

// 函数:增加队伍对象
int add_member(string leader_id, object who)
{
	int tId;
	object *nObj;
	if (!who || !who->is_user())
		return 0;
	tId = mpTeam[leader_id];
	if (!tId)
		return 0;
	nObj = get_save_2(sprintf("%d.member", tId));
	if (!nObj)
		return 0;
	nObj += ({who});
	set_save_2(sprintf("%d.member", tId), nObj);
	who->set_team_id(tId);
	who->set_group_id(get_save_2(sprintf("%d.groupid", tId)));
	check_bonus_task(leader_id); // 更新带的新手
	send_user(who, "%c%c%d", 0x54, 23, get_save_2(sprintf("%d.gain.mode", tId)));
	send_user(who, "%c%c%d", 0x54, 24, get_save_2(sprintf("%d.gain.type", tId)));
	return 1;
}

// 函数:减少队伍对象
int remove_member(string id, object who)
{
	int tId, z;
	object *nObj, map;

	if (!who || undefinedp(tId = mpTeam[id]) || tId == 0)
		return 0;
	nObj = get_save_2(sprintf("%d.member", tId));
	if (!sizeof(nObj))
		return 0;
	who->set_leader(0);
	who->set_bonus_member(0); // 清除带的新手
	send_user(who, "%c%c", 0x54, 0xff);
	nObj -= ({who, 0});
	who->set_team_id(0);
	who->set_group_id(0);
	z = get_z(who);
	if (!sizeof(nObj)) //队伍解散
	{
		CHAR_CHAR_D->init_loop_perform(who);
		send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 9111, 1, OVER_BODY, PF_STOP);
		dest_copy_scene(tId);
		map_delete(mpTeam, id);
		if (objectp(map = get_map_object(z)) && map->is_virtual_scene() && map->is_ken_map())
		{
			map->check_outmap(60, who);
		}
		remove_group_team(tId);
		delete_save_2(sprintf("%d", tId));
		return 1;
	}
	set_save_2(sprintf("%d.member", tId), nObj);
	send_user(nObj, "%c%c%d", 0x54, 0, who->get_number());

	if (sprintf("%d", who->get_number()) == id)
		change_leader(who, nObj[0]);
	else
		check_bonus_task(id);	 // 更新带的新手
	if (who->get("team_follow")) //对方跟随的状态
	{
		who->delete ("team_follow");
		send_user(who, "%c%w%w%c", 0x81, 0011, 0, EFFECT_GOOD);
		send_user(who, "%c%c%c", 0xA5, 3, 0);
	}

	if (objectp(map = get_map_object(z)) && map->is_virtual_scene() && map->get("copy_id") && !map->is_ken_map())
	{
		if (map->get("gumu_map"))
			return;
		MAP_D->add_to_void(who);
	}
	if (objectp(map = get_map_object(z)) && map->is_virtual_scene() && map->is_ken_map())
	{

		map->check_outmap(60, who);
	}

	return 1;
}

// 函数:更换队长对象
int change_leader(object leader, object who)
{
	string id0, id1;
	int tId;
	object *nObj;

	if (!leader || !who)
		return 0;

	id0 = sprintf("%d", leader->get_number());
	tId = mpTeam[id0];
	nObj = get_save_2(sprintf("%d.member", tId));
	if (undefinedp(nObj) || member_array(who, nObj) == -1)
		return 0;
	send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 9111, 1, OVER_BODY, PF_LOOP);
	send_user(get_scene_object_2(leader, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(leader), 9111, 1, OVER_BODY, PF_STOP);
	id1 = sprintf("%d", who->get_number());
	mpTeam[id1] = tId;
	map_delete(mpTeam, id0);
	set_save_2(sprintf("%d.leader", tId), id1);
	nObj -= ({who});
	nObj = ({who}) + nObj;
	set_save_2(sprintf("%d.member", tId), nObj);
	if (sizeof(nObj))
	{
		nObj->set_leader(id1);
		if ("/sys/sys/count"->get_new_person())
			send_user(nObj, "%c%c%d%d%c%s", 0x54, 1, who->get_number(), who->get_photo(), who->get_level(), who->get_name());
		else
			send_user(nObj, "%c%c%d%d%c%s", 0x54, 1, who->get_number(), who->get_armor_code(), who->get_level(), who->get_name());
		send_user(nObj, "%c%c%d%s", 0x43, 7, 0, sprintf(WHT "Hiện tại đội trưởng mới của nhóm là %s(%d).", who->get_name(), who->get_number()));
		check_bonus_task(id1); // 更新带的新手
	}
	if (who->get("team_follow")) //对方跟随的状态
	{
		who->delete ("team_follow");
		send_user(who, "%c%w%w%c", 0x81, 0011, 0, EFFECT_GOOD);
		send_user(who, "%c%c%c", 0xA5, 3, 0);
	}
	CHAR_CHAR_D->init_loop_perform(who);
	CHAR_CHAR_D->init_loop_perform(leader);
	return 1;
}

// 函数:删除队伍对象
int dismiss_team(string id)
{
	int tId;
	object *nObj;

	tId = mpTeam[id];
	nObj = get_save_2(sprintf("%d.member", tId));
	if (undefinedp(nObj))
		return 0;

	if (sizeof(nObj))
	{
		nObj->set_leader(0);
		nObj->set_team_id(0);
		nObj->set_group_id(0);
		nObj->set_bonus_member(0); // 清除带的新手
		send_user(nObj, "%c%c", 0x54, 0xff);
		CHAR_CHAR_D->init_loop_perform(nObj);
		send_user(get_scene_object_2(nObj[0], USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(nObj[0]), 9111, 1, OVER_BODY, PF_STOP);
	}
	dest_copy_scene(tId);
	map_delete(mpTeam, id);
	remove_group_team(tId);
	delete_save_2(sprintf("%d", tId));
	return 1;
}

// 函数:检查带新手任务
void check_bonus_task(string id)
{
	object leader;
	int i, size;
	int tId;
	object *nObj;

	tId = mpTeam[id];
	nObj = get_save_2(sprintf("%d.member", tId));
	if (undefinedp(nObj))
		return;

	if (!(leader = find_player(id)))
		return;
	if (leader->get_level() < 50)
		return;

	for (i = 0, size = sizeof(nObj); i < size; i++)
		if (nObj[i] && nObj[i]->get_max_level() < 30) // get_level()
		{
			leader->set_bonus_member(nObj[i]);
			return;
		}

	leader->set_bonus_member(0);
}

//改变Phân phối theo nhóm模式
void change_gain_mode(object who, string id, string arg)
{
	int mode, tId;
	string com;
	object *nObj;

	tId = mpTeam[id];
	nObj = get_save_2(sprintf("%d.member", tId));
	if (undefinedp(nObj) || !arg)
		return;
	if (sscanf(arg, "%s %d", com, mode) != 2)
		return;
	nObj -= ({0});
	if (com == "mode")
	{
		if (mode < 0 || mode > 4)
			return;
		delete_save_2(sprintf("%d.gain", tId));
		set_save_2(sprintf("%d.gain.mode", tId), mode);
		set_save_2(sprintf("%d.gain.type", tId), 1);
		send_user(nObj, "%c%c%d", 0x54, 23, mode);
		send_user(nObj, "%c%c%d", 0x54, 24, 1);
		send_user(nObj, "%c%c%d%s", 0x43, 7, 0, sprintf(WHT "Hiện tại nhóm phương thức phân phối là %s.", mpGainMode[mode]));
	}
	else if (com == "type")
	{
		if (mode < 1 || mode > 2)
			return;
		set_save_2(sprintf("%d.gain.type", tId), mode);
		send_user(nObj, "%c%c%d", 0x54, 24, mode);
		send_user(nObj, "%c%c%d%s", 0x43, 7, 0, sprintf(WHT "Hiện tại nhóm phân phối là %s trang bị", mode == 1 ? "Lam Kim" : "Hoàng Kim"));
	}
}

void before_destruct()
{
	TEAM_DATA->set_2("team_id", team_id);
	TEAM_DATA->set_2("mpTeam", mpTeam);
	TEAM_DATA->set_2("database", get_save_dbase_2());
	TEAM_DATA->set_2("items", mpItem);
	TEAM_DATA->set_2("mpGroup", mpGroup);
}
//获取队伍ID
int get_team_id() { return team_id; }
//队伍给予物品
int give_item(object me, object who, object item)
{
	int amount, total, p, itemid;
	string result;
	object owner;

	if ((owner = environment(item)) && owner->is_user()) //被Nhặt được
		return 0;
	if ((total = USER_INVENTORY_D->can_carry_3(who, item)) < 1)
	{
		if (me == who)
			send_user(me, "%c%s", '!', "Hành trang không đủ chỗ trống");
		else
			send_user(me, "%c%s", '!', who->get_name() + " hành trang không đủ chỗ trống");
		return 0;
	}
	item->delete ("team_id");
	if (item->is_record() && item->get("from"))
	{
		itemid = "/sys/sys/id"->add_max_itemid(1);
		item->set_user_id(sprintf("#%d#", itemid));
		//	log_file("itemid.dat", sprintf("%s %d %s %s\n", short_time(), itemid, item->get_name(), "/sys/item/item"->get_pawn_save_string(item)));
		total = item->get_amount();
		if (total == 0)
			total = 1;
		result = sprintf("Nhặt được %s %s,%d,%s,%s %s %s %d %s %d_%d_%d", item->get("from"), me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), item->get_name(), "/sys/item/item"->get_pawn_save_string(item), total, item->get_user_id(), get_z(me), get_x(me), get_y(me));
		//"/sys/user/cmd"->log_item(result);
	}
	if (item->is_combined())
	{
		if (total > item->get_amount())
			total = item->get_amount();

		amount = USER_INVENTORY_D->carry_combined_item(who, item, total);

		if (amount > 0 && item->set_amount(amount))
		{
			if (p = item->move2(who))
			{
				item->remove_from_scene();
				item->add_to_user(p);

				if (item->get("time"))
					item->delete ("time");
				if (item->get("winner"))
					item->delete ("winner");
			}
		}
		else
			item->add_amount(-total);
	}
	else if (p = item->move2(who))
	{
		if (item->get_bind() == 3)
			item->set_bind(4);
		item->remove_from_scene();
		item->add_to_user(p);

		if (item->get("time"))
			item->delete ("time");
		if (item->get("winner"))
			item->delete ("winner");
	}
	return 1;
}
//Phân phối theo nhóm物品
int distribute_item(object who, object item)
{
	int tId, i, size, total, iFlag, mode;
	object *member, me, him, *member1 = ({});
	string name, cTmp, color, result, from;
	mixed *mxTmp;

	tId = who->get_team_id();
	if (!tId)
		return 0;
	if (item->get("team_id") != tId) //是否该队伍的物品
		return 1;
	mode = get_save_2(sprintf("%d.gain.mode", tId));
	member = get_save_2(sprintf("%d.member", tId));
	size = sizeof(member);
	if (!size)
		return 0;
	//判断距离
	for (i = 0; i < size; i++)
	{ // khoảng cách item check kĩ
		if (distance_between(item, member[i]) && distance_between(item, member[i]) <= 30)
			continue;
		member1 += ({member[i]});
	}
	member -= ({0});
	member -= member1;
	if (!sizeof(member))
		return 0;
	if (item->is_cash()) //金钱平分
	{
		from = item->get("from");
		item->remove_from_scene();
		total = item->get_value();
		destruct(item);
		for (i = 0, size = sizeof(member); i < size; i++)
		{
			me = member[i];
			if (!me)
				continue;
			tell_user(me, "Bạn nhặt được %d lượng", total / size);
			me->add_cash2(total / size);
			me->add_gold_log("get", total / size);
			me->log_money("捡", total / size);
			if (from)
			{
				result = sprintf("Nhặt được %s %s,%d,%s,%s 金 0 %d 0 %d_%d_%d", from, me->get_name(), me->get_number(), get_ip_name(me), me->get_id(), total / size, get_z(me), get_x(me), get_y(me));
				//"/sys/user/cmd"->log_item(result);
			}
		}
		"/sys/sys/count"->add_income("get", total / size * size);
		return 1;
	}
	name = item->get_name();
	if (mode == 4 && item->get("team_turn"))
		mode = 3;
	if (mode == 1 || mode == 2 || mode == 4)
	{
		if (item->get_item_color() && item->get_item_color() != 4)
		{
			iFlag = get_save_2(sprintf("%d.gain.type", tId));
			if (iFlag && item->get_item_color() < iFlag)
				mode = 3;
		}
		else
			mode = 3;
	}
	if (mode == 0) //Tự Do
	{
		if (give_item(who, who, item))
			tell_user(who, "Bạn nhặt được %s", name);
	}
	else if (mode == 1) //Đội trưởng phân phối
	{
		//层次
		if (!who->is_leader())
			return 0;
		switch (item->get_item_color())
		{
		default:
			color = NOR;
			break;
		case 1:
			color = HIC;
			break;
		case 2:
			color = HIY;
			break;
		case 3:
			color = PPM;
			break;
		}
		size = sizeof(member);
		cTmp = "%c%c%d";
		mxTmp = ({0x54, 26, size});
		for (i = 0; i < size; i++)
		{
			cTmp += "%d";
			mxTmp += ({member[i]->get_number()});
		}
		cTmp += "%d%d%s";
		mxTmp += ({getoid(item), item->get_picid_2(), color + item->get_name()});
		//		send_user(who,"%c%c%d%d%s",0x54,26,getoid(item),item->get_picid_2(),color+item->get_name());
		send_user(who, cTmp, mxTmp);
		//		cTmp = sprintf("您打算把"HIR"%s"NOR"分配给谁呢？\n",name);
		//		for(i=0,size=sizeof(member);i<size;i++)
		//			cTmp += sprintf(ESC"%s\nteam give %d %x#\n",member[i]->get_name(),member[i]->get_number(),getoid(item));
		//		cTmp += ESC"取消";
		//		send_user(who,"%c%c%w%s",':',3,0,cTmp);
	}
	else if (mode == 2) //Phân phối theo nhóm
	{
		if (gone_time(item->get("distribute_time")) < 20)
			return;
		if (gone_time(get_save_2(sprintf("%d.gain.bet", tId))) < 20) //正在竞投
			return;
		switch (item->get_item_color())
		{
		default:
			color = NOR;
			break;
		case 1:
			color = HIC;
			break;
		case 2:
			color = HIY;
			break;
		}
		set_save_2(sprintf("%d.gain.bet", tId), time());
		item->set("distribute_time", time());
		item->set("distribute_num", sizeof(member));
		mpItem[sprintf("%x#", getoid(item))] = (["obj":item, "bet":([])]);
		send_user(member, "%c%c%d%d%d%s", 0x54, 25, getoid(item), item->get_picid_2(), 15, color + item->get_name());
		//		send_user(member,"%c%c%w%s",':',3,0,sprintf("你是否参与 %s 的竞投？\n"
		//			ESC"竞投\nteam bet %x#\n"ESC"取消",item->get_name(),getoid(item)
		//			)
		//		);
		if (iCall == 0)
			distribute_item_call();
	}
	else if (mode == 3) //Luân phiên nhặt đồ
	{
		size = sizeof(member);
		i = get_save_2(sprintf("%d.gain.turn", tId));
		if (i >= size)
			i = 0;
		for (; i < size; i++)
		{
			me = member[i];
			if (!me)
				continue;
			if (USER_INVENTORY_D->can_carry_3(me, item) < 1)
				continue;
			break;
		}
		if (i <= size - 1)
		{
			if (give_item(me, me, item))
			{
				send_user(member, "%c%c%d%s", 0x43, 7, 0, WHT + me->get_name() + " được " + name);
				set_save_2(sprintf("%d.gain.turn", tId), i + 1);
			}
		}
		else
			set_save_2(sprintf("%d.gain.turn", tId), 0);
	}
	else if (mode == 4) //Phân phối theo nhu cầu
	{
		if (gone_time(item->get("distribute_time")) < 20)
			return;
		if (gone_time(get_save_2(sprintf("%d.gain.bet", tId))) < 20) //正在竞投
			return;
		member1 = ({});
		for (i = 0, size = sizeof(member); i < size; i++)
			if (check_equip(member[i], item) != 1)
				member1 += ({member[i]});
		member -= member1;
		if (!sizeof(member))
		{
			item->set("team_turn", 1);
			return;
		}
		switch (item->get_item_color())
		{
		default:
			color = "";
			break;
		case 1:
			color = HIC;
			break;
		case 2:
			color = HIY;
			break;
		}
		set_save_2(sprintf("%d.gain.bet", tId), time());
		item->set("distribute_time", time());
		item->set("distribute_num", sizeof(member));
		mpItem[sprintf("%x#", getoid(item))] = (["obj":item, "bet":([])]);
		send_user(member, "%c%c%d%d%d%s", 0x54, 25, getoid(item), item->get_picid_2(), 15, color + item->get_name());

		//		send_user(member,"%c%c%w%s",':',3,0,sprintf("你是否参与 %s 的竞投？\n"
		//			ESC"竞投\nteam bet %x#\n"ESC"取消",item->get_name(),getoid(item)
		//			)
		//		);
		if (iCall == 0)
			distribute_item_call();
	}
	return 1;
}

//Đội trưởng phân phối物品
int leader_give_item(object me, string arg)
{
	int tId;
	string id, id1, name;
	object who, item, *nObj;

	if (!me->is_leader())
	{
		notify("Bạn không phải đội trưởng");
		return 1;
	}
	tId = me->get_team_id();
	if (!tId || sscanf(arg, "%s %s", id, id1) != 2 || get_save_2(sprintf("%d.gain.mode", tId)) != 1)
		return 0;
	nObj = get_save_2(sprintf("%d.member", tId));
	if (!sizeof(nObj))
		return 0;
	if (!objectp(who = find_char(id)))
	{
		notify("Đối phương đang ngoại tuyến");
		return 1;
	}
	if (!objectp(item = find_any_object(id1)) || !get_z(item))
	{
		notify("Vật phẩm không tồn tại");
		return 1;
	}
	if (tId != item->get("team_id")) //不能分别人的物品
	{
		notify("Bạn không thể phân phối vật phẩm");
		return 1;
	}

	name = item->get_name();
	if (give_item(me, who, item))
	{
		tell_user(who, "Bạn nhặt được %s", name);
		send_user(nObj, "%c%c%d%s", 0x43, 7, 0, sprintf(WHT "%s đem " HIR "%s" WHT " phân phối cho %s", me->get_name(), name, who->get_name()));
	}
	return 1;
}

void distribute_item_call()
{
	int i, size, *nUser, j, count, max;
	string *nId, *nId1, name;
	object item, who, who1, *nObj;
	mapping mpTmp;
	remove_call_out("distribute_item_call");
	iCall = 0;
	nId = keys(mpItem);
	size = sizeof(mpItem);
	if (!size)
		return;
	for (i = 0; i < size; i++)
	{
		item = mpItem[nId[i]]["obj"];
		nId1 = ({});
		if (!item)
		{
			nId1 += ({nId[i]});
			continue;
		}
		if (gone_time(item->get("distribute_time")) < 15)
			continue;
		nId1 += ({nId[i]});
		mpTmp = mpItem[nId[i]]["bet"];
		nUser = keys(mpTmp);
		count = sizeof(nUser);
		if (!count)
			continue;
		for (j = 0; j < count; j++) //选择最大的
		{
			who1 = find_char(nUser[j]);
			if (!who1)
				continue;
			if (mpTmp[nUser[j]] <= max)
				continue;
			max = mpTmp[nUser[j]];
			who = who1;
		}
		if (!who)
			continue;
		name = item->get_name();
		if (give_item(who, who, item))
		{
			nObj = who->get_team();
			tell_user(who, "Bạn nhận được %s", name);
			send_user(nObj, "%c%c%d%s", 0x43, 7, 0, sprintf(WHT "%s  được " HIR "%s", who->get_name(), name));
		}
	}
	nId -= nId1;
	for (i = 0, size = sizeof(nId1); i < size; i++)
		map_delete(mpItem, nId1[i]);
	if (!sizeof(nId))
		return;
	iCall = 1;
	call_out("distribute_item_call", 5);
}
//加入竞投
void add_bet(object who, string arg)
{
	int rate, num, tId, mode;
	object item, *team;
	mapping mpTmp;
	if (!arg)
		return;
	if (!arrayp(team = who->get_team()))
		return;
	if (!mapp(mpTmp = mpItem[arg]))
		return;
	item = mpTmp["obj"];
	if (!item)
		return;
	tId = who->get_team_id();
	if (item->get("team_id") != tId)
		return;
	mode = get_save_2(sprintf("%d.gain.mode", tId));
	if (mpItem[arg]["bet"][sprintf("%d", num)])
		return;
	if (mode == 4 && check_equip(who, item) != 1)
		return;
	rate = 1 + random100();
	num = who->get_number();
	mpItem[arg]["bet"][sprintf("%d", num)] = rate;
	send_user(team, "%c%c%d%s", 0x43, 7, 0, sprintf(WHT "%s tham dự cạnh đầu %s， nhận được %d", who->get_name(), item->get_name(), rate));
	if (item->add("distribute_num", -1) <= 0)
	{
		item->set("distribute_time", 0);
		set_save_2(sprintf("%d.gain.bet", tId), 0);
		distribute_item_call();
	}
}
//检查是否可以装备
int check_equip(object me, object equip)
{
	int flag, index, type;
	if (!equip)
		return 0;
	if (!(index = equip->get_equip_type()))
		return 1;
	if (index == FAMILY_TYPE)
		return 0;

	if ((flag = equip->get_gender()) && flag != me->get_gender())
		return 0;

	flag = equip->get_family();
	if (flag == 8)
		flag = 0;
	if (flag)
	{
		switch (index)
		{
		default:
			switch (me->get_fam_name())
			{
			default:
				if (flag != 8)
					flag = -1;
				break;
			case "Đào Hoa Nguyên":
				if (flag != 1)
					flag = -1;
				break;
			case "Thục Sơn":
				if (flag != 2 && flag != 9)
					flag = -1;
				break;
			case "Cấm Vệ Quân":
				if (flag != 3)
					flag = -1;
				break;
			case "Đường Môn":
				if (flag != 4)
					flag = -1;
				break;
			case "Mao Sơn":
				if (flag != 5 && flag != 9)
					flag = -1;
				break;
			case "Côn Luân":
				if (flag != 6 && flag != 9)
					flag = -1;
				break;
			case "Vân Mộng Cốc":
				if (flag != 7 && flag != 9)
					flag = -1;
				break;
			}
			break;

		case WEAPON_TYPE:
			switch (me->get_fam_name())
			{
			default:
				if (flag != 8)
					flag = -1;
				break;
			case "Đào Hoa Nguyên":
				if (flag != 1)
					flag = -1;
				break;
			case "Thục Sơn":
				if (flag != 2 && flag != 9)
					flag = -1;
				break;
			case "Cấm Vệ Quân":
				if (flag != 3)
					flag = -1;
				break;
			case "Đường Môn":
				if (flag != 4)
					flag = -1;
				break;
			case "Mao Sơn":
				if (flag != 5 && flag != 9)
					flag = -1;
				break;
			case "Côn Luân":
				if (flag != 6 && flag != 9)
					flag = -1;
				break;
			case "Vân Mộng Cốc":
				if (flag != 7 && flag != 9)
					flag = -1;
				break;
			}
			break;

		case HAND_TYPE:
			switch (me->get_fam_name())
			{
			default:
				flag = -1;
				break;
			case "Vân Mộng Cốc":
				if (flag != 7)
					flag = -1;
				break;
			case "Côn Luân":
				if (flag != 6)
					flag = -1;
				break;
			case "Mao Sơn":
				if (flag != 5)
					flag = -1;
				break;
			case "Đường Môn":
				if (flag != 4)
					flag = -1;
				break;
			case "Cấm Vệ Quân":
				if (flag != 3)
					flag = -1;
				break;
			case "Thục Sơn":
				if (flag != 2)
					flag = -1;
				break;
			case "Đào Hoa Nguyên":
				if (flag != 1)
					flag = -1;
				break;
			}
			break;
		}
		if (flag < 0)
			return 0;
	}
	else
	{
		if (index == WEAPON_TYPE)
		{
			type = equip->get_weapon_type();
			switch (me->get_fam_name())
			{
			case "Đào Hoa Nguyên":
				if (type != UNARMED)
					flag = -1;
				break;
			case "Thục Sơn":
				if (type != SWORD && type != BLADE)
					flag = -1;
				break;
			case "Cấm Vệ Quân":
				if (type != STICK && type != SPEAR)
					flag = -1;
				break;
			case "Đường Môn":
				if (type != THROWING)
					flag = -1;
				break;
			case "Mao Sơn":
				if (type != SWORD)
					flag = -1;
				break;
			case "Côn Luân":
				if (type != SWORD)
					flag = -1;
				break;
			case "Vân Mộng Cốc":
				if (type != SWORD)
					flag = -1;
				break;
			}
		}
		if (flag < 0)
			return 0;
	}
	return 1;
}
//掉落物品，记录队伍标志
void drop_item(object item, object who)
{
	item->set("team_id", who->get_team_id());
}
//加入副本场景对象
int add_copy_scene(int tId, int copy_id, object map)
{
	object *nObj;
	if (!get_save_2(sprintf("%d", tId)) || !map)
		return 0;
	set_save_2(sprintf("%d.copy.%d", tId, copy_id), map);
	return 1;
}
//获取副本场景对象
object get_copy_scene(int tId, int copy_id)
{
	return get_save_2(sprintf("%d.copy.%d", tId, copy_id));
}
//删除队伍的所有副本场景
void dest_copy_scene(int tId)
{
	int i, size;
	string *nCopy;
	mapping mpTmp;
	object map;

	mpTmp = get_save_2(sprintf("%d.copy", tId));
	if (!mapp(mpTmp))
		return;
	nCopy = keys(mpTmp);
	for (i = 0, size = sizeof(nCopy); i < size; i++)
	{
		if (!objectp(map = get_save_2(sprintf("%d.copy.%s", tId, nCopy[i]))))
			continue;
		if (map->get("gumu_map"))
			continue;

		COPY_MAP->destruct_virtual_map(map, map->get_id());
	}
}
//删除队伍的指定副本场景
void remove_copy_scene(int tId, int copy_id)
{
	object map;

	map = get_save_2(sprintf("%d.copy.%s", tId, copy_id));

	if (!map)
		return;
	COPY_MAP->destruct_virtual_map(map, map->get_id());
}
//获取队伍的团队ID
int get_group_id(int tId)
{
	return get_save_2(sprintf("%d.groupid", tId));
}
//获取团队的队伍数量
int get_group_amount(int gId)
{
	int *nMember;
	mapping mpTmp;

	mpTmp = mpGroup[gId];
	if (!mapp(mpTmp))
		return 0;
	nMember = mpTmp["members"];
	return sizeof(nMember);
}
//获取团队团队集合
int *get_group_member(int gId)
{
	int *nMember;
	mapping mpTmp;

	mpTmp = mpGroup[gId];
	if (!mapp(mpTmp))
		return 0;
	nMember = mpTmp["members"];
	return copy(nMember);
}
//创建团队（不包含队伍的）
int new_group()
{
	group_id++;
	mpGroup[group_id] = (["members":({}),
	]);
	return group_id;
}
//获取团队首支队伍编号
int get_first_group_team(int gId)
{
	int *nMember;
	mapping mpTmp;

	mpTmp = mpGroup[gId];
	if (!mapp(mpTmp))
		return 0;
	nMember = mpTmp["members"];
	if (!sizeof(nMember))
		return 0;
	return nMember[0];
}
//增加团队成员（队伍）
int add_group_team(int gId, int tId)
{
	int *nMember, i, size;
	mapping mpTmp;
	object *nObj;

	if (get_group_id(tId)) //已经是团队
		return 0;
	if (gId == 0) //创建队伍
		gId = new_group();
	if (!mapp(mpTmp = mpGroup[gId]))
		return 0;
	nMember = mpTmp["members"];
	if (member_array(tId, nMember) != -1)
		nMember -= ({tId});
	if (sizeof(nMember) >= 8)
		return 0;
	nMember += ({tId});
	mpGroup[gId] = (["members":nMember,
	]);
	set_save_2(sprintf("%d.groupid", tId), gId); //记录队伍的团队ID
	nObj = get_team_by_id(tId);
	nObj -= ({0});
	for (i = 0, size = sizeof(nObj); i < size; i++)
	{
		if (!objectp(nObj[i]))
			continue;
		nObj[i]->set_group_id(gId); //设置队员的团队ID
	}
	return gId;
}
//减少团队成员（队伍）
int remove_group_team(int tId)
{
	int *nMember, gId;
	mapping mpTmp;

	if (!(gId = get_group_id(tId)))
		return 0;
	if (!mapp(mpTmp = mpGroup[gId]))
		return 0;
	nMember = mpTmp["members"];
	if (member_array(tId, nMember) != -1)
	{
		nMember -= ({tId});
		if (sizeof(nMember))
			mpGroup[gId] = (["members":nMember, ]);
		else
			map_delete(mpGroup, gId); //没有队伍则删除
	}
	delete_save_2(sprintf("%d.groupid", tId)); //删除队伍的团队ID
	return gId;
}
//队伍离开团队
int leave_group(int tId)
{
	object *nObj;
	if (!tId)
		return 0;
	remove_group_team(tId);
	nObj = get_team_by_id(tId);
	nObj->set_group_id(0);
	return 1;
}