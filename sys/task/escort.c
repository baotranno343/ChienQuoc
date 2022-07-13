
#include <time.h>
#include <ansi.h>
#include <cmd.h>
#include <music.h>
#include <task.h>
#include <time.h>
#include <equip.h>
inherit DBASE_F;
inherit SAVE_F;
static mapping npc_num = ([0:({
								 "Hàn Quốc",
								 "Triệu Mộc",
								 "220,176",
							 }),
						   1:({
								 "Tần Quốc",
								 "Mã Hiển",
								 "231,148",
							 }),
						   2:({
								 "Ngụy Quốc",
								 "Trình Lâm Khai",
								 "106,146",
							 }),
						   3:({
								 "Triệu Quốc",
								 "Lí Phòng",
								 "214,239",
							 }),
]);
int num; //第几期
static string *cityname = ({
	"Tề Quốc",
	"Sở Quốc",
	"Tần Quốc",
	"Yên Quốc",
	"Triệu Quốc",
	"Ngụy Quốc",
	"Hàn Quốc",
});
int iStart1, iFinish1, iFinish2, iFinish3, iFlag;
int iGame;
// 函数:生成二进制码
void SAVE_BINARY() {}
string get_save_file() { return "data/yunbiao" SAVE_EXTENSION; }

void do_task_start(object who, object me, string arg);
void do_task_finish(object who, object me);
void do_task_cancel(object who, object me);
void clear_task_desc(object who);
void send_task_list(object who);

// 函数:构造处理
void create()
{
	restore();
	call_out("check_time", 3);
}
// 函数:对话处理(镖头)
void do_look(object who, object me)
{
	int id = getoid(me), iTime;
	string cmd1 = sprintf("talk %x# tasklist\n", id);
	string tmp = "";
	iTime = time();
	//	if ( who->get_legend(TASK_NEWBIE_00, 13) && !who->get_legend(TASK_NEWBIE_00, 14) )
	//		tmp = ESC HIY "Tìm ta nói chuyện.\n" + sprintf( "talk %x# welcome.1\n", id );
	if (who->get_level() >= 30 && !who->get_legend(TASK_49, 13) && !who->get_quest("escort.flag"))
		tmp = ESC HIY "Tìm tòi hư thực.\n" + sprintf("talk %x# welcome.3\n", id);
	if (who->get_legend(TASK_2_00, 14) && !who->get_legend(TASK_2_00, 15))
		tmp = ESC HIY "Tìm ta nói chuyện.\n" + sprintf("talk %x# welcome.5\n", id);
	if (who->get_legend(TASK_2_00, 15) && !who->get_legend(TASK_2_00, 16))
		tmp = ESC HIY "Bái phỏng Tả Khâu Minh.\n" + sprintf("talk %x# welcome.7\n", id);
	//	tmp += ESC HIG "Phiêu Vương Bá Chiến\n" + sprintf( "talk %x# welcome.11\n", id );
	if (iTime > iFinish1 && iTime < iFinish3)
		tmp += ESC HIG "Nhận lấy tiêu vương ban thưởng \n" + sprintf("talk %x# welcome.13\n", id);

	send_user(who, "%c%s", ':', me->get_name() + ":\n    Hiện tại trong tiêu cục nhân lực đang thiếu, nếu ngươi đạt trên cấp 30 có thể tìm ta để nhận nhiệm vụ áp tiêu !\n" + tmp + ESC "Nhận nhiệm vụ áp tiêu\n" + cmd1 + ESC "Rời khỏi\nCLOSE\n");
}

// 变量:随机对话
static string *TalkTable = ({
	"Đầu năm nay rối loạn, muốn áp tiêu cũng không dễ dàng...",
	"Muốn tìm Tiêu Cục Kinh Đô hộ tống hành hoá nhưng hắn không rảnh...",
	"Muốn tìm Tiêu Cục Kinh Đô hộ tống người thân nhưng hắn không rảnh...",
	"Chu Quốc Kinh Đô Tiêu Cục võ nghệ cao cường, trời sinh tính tình hào sảng, thật là một hảo hán !",
});

static int sizeof_talk = sizeof(TalkTable);

// 函数:对话处理(客户)
void do_look_2(object who, object me)
{
	int id;
	string result;
	if (who->get_quest("escort.flag")																						  // Nhiệm vụ áp tiêu
		&& who->get_quest("escort.leader") == 1																				  // 队长完成
		&& who->get_quest("escort.name") == me->get_name() && who->get_quest("escort.city") + " Quốc" == me->get_city_name()) // 找对人了
	{
		if (who->get("escort.finish") == 0)
		{
			who->set("escort.finish", 1);
			if (who->get_quest("escort.flag") == 1)
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s\n Nhanh như vậy đã đưa đến rồi à, thật là nhân quả không tồi !\n" ESC "Hoàn thành nhiệm vụ\nlook %x#\n", me->get_name(), id = getoid(me)));
			else
				send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s\n Cám ơn ngươi an toàn đưa hắn đến, hãy nhận lấy một chút tâm ý của ta.\n" ESC "Hoàn thành nhiệm vụ\nlook %x#\n", me->get_name(), id = getoid(me)));
		}
		else
		{
			who->delete ("escort.finish");
			do_task_finish(who, me);
		}
		return;
	}
	result = sprintf("%s:\n%s\n", me->get_name(), TalkTable[random(sizeof_talk)]);
	if (me->is_seller())
		result += sprintf(ESC "Mua đạo cụ\nlist %x#\n", getoid(me));
	result += ESC "Rời khỏi\n";
	send_user(who, "%c%s", ':', result);
}

//int check_level(object who, object me,int level)
//{
//	int i,size;
//	object *team;
//
//	if( !arrayp( team = who->get_team() ) || !who->is_leader() )
//        	return 1;
//	for(i=0,size=sizeof(team);i<size;i++)
//	{
//		if ( team[i]->get_level() < level )
//		{
//			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),me->get_name()+sprintf(":\n   Không được không được, đồng đội của người đẳng cấp chưa đủ đủ %d Cấp, ta không cách nào đem nhiệm vụ ủy thác cho ngươi.",level));
//			return 0;
//		}
//	}
//	return 1;
//}
int check_level(object who, object me, int level)
{

	if (who->get_level() < level)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + sprintf(":\n    Cấp bậc của ngươichưa tới %d cấp, ta không thể giao nhiệm vụ cho ngươi", level));
		return 0;
	}
	return 1;
}
int check_before_quest(object who, object me, int flag, int gold)
{
	//	object *team;
	int size, i;

	if (who->get_quest("escort.baiwang"))
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Hãy làm nhiệm vụ Hộ Tống đi, còn đứng đây làm chi !\n" ESC "Rời khỏi");
		return 0;
	}
	if (who->get_quest("escort.flag"))
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Sao ngươi còn đứng đây, còn không mau đi đi ? nếu thật sự không tìm thấy nơi đến  có thể hỏi thăm Thủ Vệ !\n" ESC "Rời khỏi");
		return 0;
	}
	//        if( arrayp( team = who->get_team() ) && !who->is_leader() )
	//        {
	////                send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), me->get_name()+":\n   Giao nhiều tiền thế chấp như vậy, ngươi có thể gánh nổi trọng trách sao? Hay là gọi người nào có thể đảm đương tới đi!\n"ESC"Rời khỏi"  );
	//                return 0;
	//        }
	//        if( ( size = sizeof(team) ) > 2 )
	//        {
	//                send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), me->get_name()+":\n   Các ngươi nhiều người như vậy, đến lúc đó ban thưởng có thể sẽ phân chia không đồng đều, có ý kiến, hay là người ít điểm tới tìm ta.\n"ESC"Rời khỏi"  );
	//                return 0;
	//        }
	if (who->get_cash() < gold)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Không phải là ta không nghĩ tới việc giao nhiệm vụ cho ngươi, nhưng nếu ngươi lỡ thất bại hộ tống thì ta lấy gì bồi thường đây !\n" ESC "Rời khỏi");
		return 0;
	}
	if (flag && gone_time(who->get_quest("escort.quest")) < 180)
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Vận tiêu phải là người có võ nghệ cao cường, còn phải sáng suốt nữa, ta đã cho ngươi một cơ hội nhưng ngươi không biết quý trọng, thôi thì để lần sau vậy\n" ESC "Rời khỏi");
		return 0;
	}
	if (who->get_save_2("apTieu.luot") >= 2 && who->get_save_2("apTieu.ngay") == localtime(time())[7])
	{
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Mỗi ngày chỉ có thể Áp Tiêu 2 lần\n" ESC "Rời khỏi");
		return 0;
	}
	return 1;
}
//接受任务
void accept_task(object who, object me)
{
	object *team, npc, item;
	string name, city, npcname;
	int z, x0, y0, x1, y1, p, size, flag, x, y, gold, level;

	gold = who->get("escort.gold");
	level = who->get("escort.level");
	who->delete ("escort.gold");
	who->delete ("escort.level");
	if (!gold)
		return;
	if (check_before_quest(who, me, 0, gold) != 1)
		return;
	if (check_level(who, me, level) != 1)
		return;
	team = who->get_team();
	size = sizeof(team);
	flag = who->get("escort.flag");
	name = who->get("escort.name");
	city = who->get("escort.tcity");
	x = who->get("escort.x");
	y = who->get("escort.y");
	if (flag == 0 || !stringp(name) || !stringp(city))
		return;

	switch (flag)
	{
	default:
		if (sizeof_inventory(who, 1, MAX_CARRY) >= MAX_CARRY)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), me->get_name() + ":\n    Hành trang không đủ 1 chỗ trống !");
			return;
		}

		item = new ("/item/std/8100");
		if (p = item->move(who, -1))
			item->add_to_user(p);

		flag = 1;
		who->add_cash(-gold);
		who->add_gold_log("biao", -gold);
		who->log_money("Vận tiêu", -gold);
		"/sys/sys/count"->add_use("biao", gold);
		who->set_quest("escort.escort", item->get_name());
		break;

	case 2:
		npc = new ("/npc/task/8100");
		npc->set_name(name + npc->get_name() + sprintf("(%d)", who->get_number()));
		npc->set_walk_speed(3);
		npcname = npc->get_name();
		z = get_z(who);
		x0 = get_x(who);
		y0 = get_y(who);
		if (p = get_valid_xy(z, x0, y0, IS_CHAR_BLOCK))
		{
			x1 = p / 1000;
			y1 = p % 1000;
			npc->add_to_scene(z, x1, y1, get_front_xy(x1, y1, x0, y0));
			npc->set_owner(who);
			who->to_front_xy(x1, y1);
		}

		flag = 2;
		who->add_cash(-gold);
		who->add_gold_log("biao", -gold);
		who->log_money("Vận tiêu", -gold);
		"/sys/sys/count"->add_use("biao", gold);
		who->set_quest("escort.escort", sprintf("%x#", getoid(npc)));
		who->set_quest("escort.npc", npc);
		break;
	}

	who->delete_quest("escort.id");
	who->delete_quest("escort.member");
	who->set_quest("escort.leader", 1);
	who->set_quest("escort.city", city);
	who->set_quest("escort.name", name);
	who->set_quest("escort.time", time());
	who->set_quest("escort.flag", flag);
	who->set_quest("escort.x", x);
	who->set_quest("escort.y", y);
	who->set_quest("escort.gold", gold);
	who->set_save("cambayquest", 1);
	if (stringp(npcname))
		who->set_quest("escort.npcname", npcname);

	who->delete_quest("escort.random"); // 记录随机事件
	who->delete_quest("escort.robber");
	who->delete_quest("escort.robber#");
	if (who->get_save_2("apTieu.ngay") != localtime(time())[7])
	{
		who->set_save_2("apTieu.luot", 0);
		who->set_save_2("apTieu.ngay", localtime(time())[7]);
	}

	who->add_save_2("apTieu.luot", 1);

	send_task_list(who);

	//	//询问队友是否加入
	//        if( size == 2 && inside_screen_2( team[0], team[1] ) )    // 组队完成
	//        {
	//        	team -= ({who});
	//        	team[0]->set("escort.join",who->get_number());
	//        	team[0]->set("escort.time",who->get_quest("escort.time"));
	//        	send_user(team[0],"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s\n    %s Đã tiếp nhận Nhiệm vụ áp tiêu, ngươi có muốn cùng hiệp trợ?\n"ESC"Tiếp nhận \ntalk %x# join\n"ESC"Hủy bỏ",me->get_name(),who->get_name(),getoid(me)));
	//        }
}
//加入任务
void join_task(object who, object npc)
{
	int size;
	string id;
	object *team, leader;

	if (who->get_quest("escort.flag") || who->is_leader())
		return;
	team = who->get_team();
	if ((size = sizeof(team)) < 2 || gone_time(who->get("escort.time")) > 2400)
		return;
	id = who->get_leader();
	leader = find_player(id);
	if (!objectp(leader) || !inside_screen_2(who, leader) || who->get("escort.join") != leader->get_number() || who->get("escort.time") != leader->get_quest("escort.time"))
		return;
	who->delete ("escort.join");
	who->delete ("escort.time");
	who->delete_quest("escort.leader");
	who->set_quest("escort.city", leader->get_quest("escort.city"));
	who->set_quest("escort.name", leader->get_quest("escort.name"));
	who->set_quest("escort.time", leader->get_quest("escort.time"));
	who->set_quest("escort.flag", leader->get_quest("escort.flag"));
	who->set_quest("escort.x", leader->get_quest("escort.x"));
	who->set_quest("escort.y", leader->get_quest("escort.y"));
	who->set_quest("escort.npcname", leader->get_quest("escort.npcname"));
	who->set_save("cambayquest", 1);
	who->delete_quest("escort.random"); // 记录随机事件
	who->delete_quest("escort.robber");
	who->delete_quest("escort.robber#");
	send_task_list(who);

	who->set_quest("escort.id", leader->get_number());
	who->set_quest("escort.member", leader->get_name());
	leader->set_quest("escort.id", who->get_number());
	leader->set_quest("escort.member", who->get_name());
}
// 函数:开始任务
void do_task_start(object who, object me, string arg)
{
	object map, *team, item;
	string name, result, city;
	int z, x, y, p, size, gold, flag, level;

	if (!stringp(arg))
		return;
	if (who->get_legend(TASK_49, 13) && !who->get_legend(TASK_49, 14))
	{
		send_user(who, "%c%s", '!', "Ngươi đang thử vận tiêu");
		return;
	}
	flag = to_int(arg);
	switch (flag)
	{
	case 1:
		if (who->get_level() < 30)
		{
			return;
		}
		gold = 30000;
		level = 30;
		break;
	case 2:
		if (who->get_level() < 40)
		{
			return;
		}
		gold = 40000;
		level = 40;
		break;
	case 3:
		// if (who->get_level() < 40)
		// {
		// 	return;
		// }
		if (who->get_level() < 40 || "sys/party/party_x2_quest_30"->get_aptieu_x2() != 1)
		{
			return;
		}
		gold = 60000;
		level = 40;
		break;
	/*	case 3:
			gold = 100000;
			level = 70;
			break;*/
	default:
		return;
	}
	if (check_before_quest(who, me, 1, gold) != 1)
		return;
	if (check_level(who, me, level) != 1)
		return;
	name = QUEST_ESCORT->get_quest();

	// switch (random(2))
	// {
	// default:
	p = QUEST_ESCORT->get_xy_point(name);
	city = cityname[random(sizeof(cityname))];
	z = p / 1000000;
	x = (p % 1000000) / 1000;
	y = (p % 1000000) % 1000;
	if (!objectp(map = get_map_object(z)) || !map->is_scene())
		return;
	result = sprintf("%s:\n    Trước đó vài ngày%s đại quan uỷ thác ta đem Rương Bạc vận chuyển tới %s, %s ngay tại " HIR " %s Quốc (%d,%d) " NOR ".Nhưng ngươi nên nhớ khi áp tiêu không được đi xa phu hay dùng đạo cụ, nếu không sẽ thất bại !\n", me->get_name(), city, name, name, map->get_name(), x, y);
	who->set("escort.name", name);
	who->set("escort.scity", city);
	who->set("escort.tcity", map->get_name());
	who->set("escort.flag", 1);
	// 	break;
	// case 1:
	// 	p = QUEST_ESCORT->get_xy_point(name);
	// 	z = p / 1000000;
	// 	x = (p % 1000000) / 1000;
	// 	y = (p % 1000000) % 1000;
	// 	if (!objectp(map = get_map_object(z)) || !map->is_scene())
	// 		return;
	// 	result = sprintf("%s:\n    Nơi này có vị khách thăm hỏi %s, cho nên ngươi hãy hộ tống %s tới %s Quốc (%d,%d),nhưng ngươi phải nhớ khi áp tiêu không được đi xa phu hay dùng đạo cụ, nếu không sẽ thất bại !\n", me->get_name(), name, name, map->get_name(), x, y);
	// 	who->set("escort.name", name);
	// 	who->set("escort.flag", 2);
	// 	who->set("escort.tcity", map->get_name());
	// 	who->set("escort.x", x);
	// 	who->set("escort.y", y);
	// 	break;
	// }
	who->set_quest("escort.quest", time());
	who->set("escort.gold", gold);
	who->set("escort.level", level);
	result += sprintf(ESC "Nhận\ntalk %x# accept\n", getoid(me));
	item = who->get_equip(HAND_TYPE);
	if (item && item->get_item_number() == 10001078)
		result += sprintf(ESC "Rời khỏi\ntalk %x# welcome.cancel\n", getoid(me));
	else
		result += ESC "Rời khỏi";
	send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), result);
}
//清除任务变量
void clear_task(object who)
{
	who->delete_quest("escort.flag");
	who->delete_quest("escort.leader");
	who->delete_quest("escort.time");
	who->delete_quest("escort.name");
	who->delete_quest("escort.escort");
	who->delete_quest("escort.npc");
	who->delete_quest("escort.npcname");
	who->delete_quest("escort.x");
	who->delete_quest("escort.y");
	who->delete_quest("escort.gold");

	who->delete_quest("escort.id");
	who->delete_quest("escort.member");

	who->delete_quest("escort.random");
	who->delete_quest("escort.robber");
	who->delete_quest("escort.robber#");
	who->delete_quest("escort.biaowang");
	who->delete_save("cambayquest", 1);
}
// 函数:结束任务
void do_task_finish(object who, object me)
{
	object member, npc, item;
	string name, file;
	int iTime, id, p, gold, exp, flag, escortgold;
	mixed *mixTime; // khai báo mixTime ( quan trọng, nhớ  có dấu * ở trước )
	iTime = time(); // khai báo Time
	mixTime = localtime(iTime);
	if (who->get_quest("escort.flag")																						  // Nhiệm vụ áp tiêu
		&& who->get_quest("escort.leader") == 1																				  // 队长完成
		&& who->get_quest("escort.name") == me->get_name() && who->get_quest("escort.city") + " Quốc" == me->get_city_name()) // 找对人了
	{
		escortgold = who->get_quest("escort.gold");
		switch (who->get_quest("escort.flag"))
		{
		default:
			if (objectp(npc = who->get_quest("escort.robber#")) // 寻找蒙面人
				&& npc->is_escort_robber())
			{
				notify(npc->get_name() + "Xuất hiện, bạn không thể hoàn thành nhiệm vụ !");
				return;
			}
			flag = 1;
			name = who->get_quest("escort.escort");
			if (!(item = present("Vật Phẩm Quý Bấu", who, 1, MAX_CARRY * 4)))
			{
				send_user(who, "%c%s", '!', "Bạn đang hộ tống gì ?");
				return;
			}
			item->remove_from_user();
			destruct(item);
			break;

		case 2:
			flag = 2;
			name = who->get_quest("escort.escort");
			if (npc = find_char(name))
			{
				if (!inside_screen_2(me, npc))
				{
					send_user(who, "%c%s", '!', "Bạn hộ tống người !");
					return;
				}
				npc->remove_from_scene();
				destruct(npc);
			}
			else
			{
				send_user(who, "%c%s", '!', "Bạn hộ tống người !");
				return;
			}
			break;
		}

		if (flag == 1											// 护送物品
			&& gone_time(who->get_quest("escort.time")) > 2400) // 超过 40 分钟
			flag = 0;

		if ((id = who->get_quest("escort.id")) && (member = find_player(sprintf("%d", id))) && inside_screen_2(me, member) && member->get_quest("escort.time") == who->get_quest("escort.time")) // 组队完成
		{

			send_user(who, "%c%c%d%w%w", 0x54, 12, getoid(who), -1, -1); // 借用 getoid(who)
			who->set_task_xy(0);										 // 清除任务坐标

			if (flag)
			{
				gold = escortgold + escortgold * 1 * who->get_online_rate() / 100;
				if ("sys/party/party_x2_quest_30"->get_aptieu_x2() == 1)
				{
					if (localtime(time())[2] == localtime(who->get_task("escort.time"))[2])
						gold += escortgold;
				}

				// if ((mixTime[TIME_HOUR] == 9 && mixTime[TIME_MIN] > 30) || (mixTime[TIME_HOUR] == 10) || (mixTime[TIME_HOUR] == 19 && mixTime[TIME_MIN] > 30) || (mixTime[TIME_HOUR] == 20))
				// {
				// 	gold += gold;
				// }

				// if (mixTime[TIME_HOUR] % 2 == 0)
				// {
				// 	gold += gold;
				// }
				who->add_cash(gold);
				who->add_gold_log("biao", gold);
				exp = 500;
				exp = exp * who->get_online_rate() / 100;
				who->add_exp(exp);
				//	"sys/sys/test_db"->add_yuanbao(who,5);
				who->add_log("$escort", gold - escortgold);
				who->add_log("&escort", exp);
				who->add_log("#escort", 1);
			}
			else
			{
				gold = escortgold;
				who->add_cash(gold);
				who->add_gold_log("biao", gold);
				exp = 0; // who->add_exp(exp);
					//	"sys/sys/test_db"->add_yuanbao(who,5);
			}
			clear_task(who);
			clear_task_desc(who);
			"/sys/sys/count"->add_income("biao", gold);
			who->log_money("运镖", gold);
			send_user(who, "%c%w", 0x0d, MUSIC_TASK);
			log_file("aptieu.txt", sprintf("%s : %s (%d) đã hoàn thành nhiệm vụ áp tiêu, Ngân Lượng: %+d \n", short_time(time()), who->get_name(), who->get_number(), gold));
			send_user(who, "%c%s", ';', sprintf("Bạn hoàn thành nhiệm vụ áp tiêu, Ngân lượng %+d, Kinh nghiệm %+d.", gold, exp));

			send_user(member, "%c%c%d%w%w", 0x54, 12, getoid(member), -1, -1); // 借用 getoid(member)
			member->set_task_xy(0);											   // 清除任务坐标

			if (flag)
			{
				gold = escortgold * 1 * member->get_online_rate() / 100;

				if ("sys/party/party_x2_quest_30"->get_aptieu_x2() == 1)
				{
					if (localtime(time())[2] == localtime(who->get_task("escort.time"))[2])
						gold += escortgold;
				}

				member->add_cash(gold);
				member->add_gold_log("biao", gold);
				exp = 500 * member->get_online_rate() / 100;
				member->add_exp(exp);
				//	"sys/sys/test_db"->add_yuanbao(who,5);
				member->add_log("$escort", gold);
				member->add_log("&escort", exp);
				member->add_log("#escort", 1);
				who->log_money("运镖", gold);
				"/sys/sys/count"->add_income("biao", gold);
			}
			else
			{
				gold = 0; // member->add_cash(gold);  member->add_gold_log("biao", gold);
				exp = 0;  // member->add_exp(exp);
			}

			clear_task(member);
			clear_task_desc(member);
			send_user(member, "%c%w", 0x0d, MUSIC_TASK);
			send_user(member, "%c%s", ';', sprintf("Bạn hoàn thành nhiệm vụ áp tiêu, Ngân lượng %+d, Kinh nghiệm %+d", gold, exp));
			log_file("aptieu.txt", sprintf("%s : %s (%d) đã hoàn thành nhiệm vụ áp tiêu, Ngân Lượng: %+d \n", short_time(time()), member->get_name(), member->get_number(), gold));
		}
		else // 独自完成
		{

			send_user(who, "%c%c%d%w%w", 0x54, 12, getoid(who), -1, -1); // 借用 getoid(who)
			who->set_task_xy(0);										 // 清除任务坐标

			if (flag)
			{
				gold = escortgold + escortgold * 1 * who->get_online_rate() / 100;
				if ("sys/party/party_x2_quest_30"->get_aptieu_x2() == 1)
				{
					if (localtime(time())[2] == localtime(who->get_task("escort.time"))[2])
						gold += escortgold;
				}

				who->add_cash(gold);
				who->add_gold_log("biao", gold);
				exp = 500 * who->get_online_rate() / 100;
				who->add_exp(exp);
				//	"sys/sys/test_db"->add_yuanbao(who,5);
				who->add_log("$escort", gold - escortgold);
				who->add_log("&escort", exp);
				who->add_log("#escort", 1);
			}
			else
			{
				gold = escortgold;
				who->add_cash(gold);
				who->add_gold_log("biao", gold);
				exp = 0; // who->add_exp(exp);
					//	"sys/sys/test_db"->add_yuanbao(who,5);
			}
			clear_task(who);
			clear_task_desc(who);
			who->log_money("运镖", gold);
			"/sys/sys/count"->add_income("biao", gold);
			send_user(who, "%c%w", 0x0d, MUSIC_TASK);
			send_user(who, "%c%s", ';', sprintf("Bạn hoàn thành nhiệm vụ áp tiêu, Ngân lượng %+d, Kinh nghiệm %+d.", gold, exp));
			log_file("aptieu.txt", sprintf("%s : %s (%d) đã hoàn thành nhiệm vụ áp tiêu, Ngân Lượng: %+d \n", short_time(time()), who->get_name(), who->get_number(), gold));
		}
		"/sys/sys/count"->add_task("运镖", 1);
		SAY_CMD->say(who, "#80");
	}
}

// 函数:取消任务
void do_task_cancel(object who, object me)
{
	object npc, item;
	int gold;

	who->delete ("tasklist");
	if (who->get_quest("escort.flag")) // Nhiệm vụ áp tiêu
	{
		if (gone_time(who->get_quest("escort.time")) < 180)
		{
			send_user(who, "%c%s", '!', "sau 3 phút mới có thể huỷ bỏ nhiệm vụ");
			return;
		}

		if (who->get_quest("escort.leader") == 1) // 队长取消
		{
			while (item = present("Vật Phẩm Quý Bấu", who, 1, MAX_CARRY * 4))
			{
				item->remove_from_user();
				destruct(item);
			}
			if (npc = find_char(who->get_quest("escort.escort")))
			{
				npc->remove_from_scene();
				destruct(npc);
			}

			who->delete_quest("escort.flag");
			who->delete_quest("escort.leader");
			who->delete_quest("escort.time");
			who->delete_quest("escort.name");
			who->delete_quest("escort.escort");
			who->delete_quest("escort.npc");

			who->delete_quest("escort.id");
			who->delete_quest("escort.member");

			who->delete_quest("escort.random");
			who->delete_quest("escort.robber");
			who->delete_quest("escort.robber#");
			who->delete_save("cambayquest");
			gold = 75000;
			who->add_cash(gold);
			who->add_gold_log("biao", gold);
			who->log_money("Vận tiêu", gold);

			write_user(who, ECHO "Bạn huỷ bỏ nhiệm vụ áp tiêu, nhận lại %d lượng", gold);
			"/sys/sys/count"->add_income("biao", gold);

			who->add_log("$escort2", gold - 100000);
			// who->add_log("&escort2", exp);
			who->add_log("#escort2", 1);
		}
		else // 队员取消
		{
			who->delete_quest("escort.flag");
			who->delete_quest("escort.leader");
			who->delete_quest("escort.time");
			who->delete_quest("escort.name");
			who->delete_quest("escort.escort");
			who->delete_quest("escort.npc");

			who->delete_quest("escort.id");
			who->delete_quest("escort.member");

			who->delete_quest("escort.random");
			who->delete_quest("escort.robber");
			who->delete_quest("escort.robber#");
			who->delete_save("cambayquest");
			write_user(who, ECHO "Bạn huỷ bỏ nhiệm vụ áp tiêu");
		}
	}
}

void task_giveup(object who)
{
	object npc, item;
	int gold;

	if (who->get_quest("escort.flag")) // Nhiệm vụ áp tiêu
	{
		if (gone_time(who->get_quest("escort.time")) < 180)
		{
			item = who->get_equip(HAND_TYPE);
			if (item && item->get_item_number() == 10001078)
			{
				send_user(who, "%c%c%s", 0x59, 1, sprintf("Ngươi sử dụng 'Mãn thiên quá hải phù' để giãn cách thời gian nhiệm vụ?\n" ESC "%c\n" ESC "use %x# escort\n", 1, getoid(item)));
				return;
			}
			send_user(who, "%c%s", '!', "Sau 3 phút mới có thể huỷ bỏ nhiệm vụ !");
			return;
		}

		if (who->get_quest("escort.leader") == 1) // 队长取消
		{
			while (item = present("Vật Phẩm Quý Bấu", who, 1, MAX_CARRY * 4))
			{
				item->remove_from_user();
				destruct(item);
			}
			if (npc = find_char(who->get_quest("escort.escort")))
			{
				npc->remove_from_scene();
				destruct(npc);
			}

			gold = who->get_quest("escort.gold") * 3 / 4;
			who->add_cash(gold);
			who->add_gold_log("biao", gold);
			who->log_money("Vận tiêu", gold);
			write_user(who, ECHO "Bạn huỷ bỏ nhiệm vụ áp tiêu, nhận lại %d lượng", gold);
			"/sys/sys/count"->add_income("biao", gold);

			who->add_log("$escort2", gold - who->get_quest("escort.gold"));
			who->add_log("#escort2", 1);
		}
		else // 队员取消
		{
			send_user(who, "%c%s", ';', "Bạn đã huỷ bỏ nhiệm vụ, nhưng vẫn có thể nhận nhiệm vụ vào lần sau");
		}
		clear_task(who);
		clear_task_desc(who);
	}
}

void send_task_list(object who)
{
	int iFlag;

	if (iFlag = who->get_quest("escort.flag"))
	{
		if (iFlag == 1) // 1. Nhiệm vụ áp tiêu(物品)
		{
			send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_ESCORT, "Nhiệm vụ áp tiêu");
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ESCORT, 1, "Hộ tống phiêu ngân");
		}
		else if (iFlag == 2) // 2. Nhiệm vụ áp tiêu(人物)
		{
			send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_ESCORT, "Nhiệm vụ áp tiêu");
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ESCORT, 2, "Hộ tống người quan trọng");
		}
		else if (iFlag == 3) // Phiêu vương bá chiến
		{
			send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_ESCORT, "Nhiệm vụ áp tiêu");
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ESCORT, 3, "Tiêu vương tranh bá chiến");
		}
	}
}

void clear_task_desc(object who)
{
	send_user(who, "%c%c%c%w%w%s", 0x51, 1, 3, 1, TID_ESCORT, "");
	send_user(who, "%c%c%c%w%s", 0x51, 1, 1, TID_ESCORT, "");
	send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ESCORT, 1, "");
	send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ESCORT, 2, "");
	send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ESCORT, 3, "");
}
//队员脱离队伍取消任务;队长脱离队伍,队员取消任务
void team_giveup(object who)
{
	object member;
	if (!who->get_quest("escort.flag"))
		return;
	if (who->get_quest("escort.leader") == 1)
	{
		member = find_player(sprintf("%d", who->get_quest("escort.id")));
		if (objectp(member))
		{
			clear_task(member);
			clear_task_desc(member);
			send_user(member, "%c%s", ';', "Bởi vì đội trưởng rời nhóm, nhiệm vụ áp tiêu bị huỷ bỏ");
		}
	}
	else
	{
		send_user(who, "%c%s", ';', "Bạn huỷ bỏ nhiệm vụ áp tiêu");
		member = find_player(sprintf("%d", who->get_quest("escort.id")));
		if (objectp(member))
			send_user(member, "%c%s", ';', who->get_name() + "Đã rời khỏi đội ngũ, ngươi tiếp tục có lên nha");
		clear_task(who);
		clear_task_desc(who);
	}
}

void do_task_list(object who, object me)
{
	int level, id;
	string tmp = "";

	if (check_before_quest(who, me, 1, 0) != 1)
		return;
	level = who->get_level();
	if (level < 30)
	{
		send_user(who, "%c%s", '!', "Cấp bậc không đủ 30");
		return;
	}
	if (who->get_legend(TASK_49, 13) && !who->get_legend(TASK_49, 14))
	{
		send_user(who, "%c%s", '!', "Ngươi ngay tại thử vận tiêu đâu");
		return;
	}
	id = getoid(me);
	if (level >= 30)
		tmp = sprintf(ESC "Thế chấp 30.000 lượng, đẳng cấp 40 có thể có thêm thế chấp\ntalk %x# task.1\n", id);
	if (level >= 40)
	{
		tmp += sprintf(ESC "Thế chấp 40.000 lượng\ntalk %x# task.2\n", id);
	}
	if (level >= 40 && "sys/party/party_x2_quest_30"->get_aptieu_x2() == 1)
	{
		tmp += sprintf(ESC "Thế chấp 60.000 lượng - Phần Thưởng x2 yêu cầu đẳng cấp 40 trở lên\ntalk %x# task.3\n", id);
	}
	/*	if ( level >=50 )
		tmp += sprintf(ESC "Thế chấp 80.000 lượng\ntalk %x# task.2\n",id);
	if ( level >= 70 )
		tmp += sprintf(ESC "Thế chấp 100.000 lượng\ntalk %x# task.3\n",id);*/

	send_user(who, "%c%s", ':', me->get_name() + ":\n    Ngươi nghĩ muốn áp tiêu bao nhiêu tiền ?\n" + tmp + ESC "Rời khỏi.\nCLOSE\n");
}
//镖王争霸
void check_biaowang(object me, object who, int iTime)
{
	int i, j, id, id1, pos, size;
	mapping mpTmp;
	if (time() > iFinish1)
		return;

	id = who->get_number();
	if (get_save_2(sprintf("player.%d", id)))
	{
		//找到之前的记录
		if (get_save_2(sprintf("sys/party/party_x2_quest_30", id)) > iTime)
		{
			set_save_2(sprintf("player.%d.time", id), iTime);
			pos = get_save_2(sprintf("player.%d.pos", id));
		}
	}
	else if ((size = get_save_2("biaowang.size")) < 10)
	{
		//插入新记录
		pos = size + 1;
		set_save_2(sprintf("biaowang.%d", pos), id);
		set_save_2(sprintf("player.%d.time", id), iTime);
		set_save_2(sprintf("player.%d.account", id), who->get_id());
		set_save_2(sprintf("player.%d.name", id), who->get_name());
		set_save_2(sprintf("player.%d.id", id), who->get_number());
		set_save_2(sprintf("player.%d.pos", id), pos);
		set_save_2("biaowang.size", pos);
	}
	else
	{
		//比较时间最多的
		id1 = get_save_2(sprintf("biaowang.%d", size));
		if (get_save_2(sprintf("player.%d.time", id1)) > iTime)
		{
			pos = size;
			delete_save_2(sprintf("player.%d", id1)); //删除
			set_save_2(sprintf("biaowang.%d", size), id);
			set_save_2(sprintf("player.%d.time", id), iTime);
			set_save_2(sprintf("player.%d.account", id), who->get_id());
			set_save_2(sprintf("player.%d.name", id), who->get_name());
			set_save_2(sprintf("player.%d.id", id), who->get_number());
			set_save_2(sprintf("player.%d.pos", id), pos);
		}
	}
	if (pos) //重新排序
	{
		for (i = pos; i > 1; i--)
		{
			id = get_save_2(sprintf("biaowang.%d", i));
			id1 = get_save_2(sprintf("biaowang.%d", i - 1));
			if (get_save_2(sprintf("player.%d.time", id1)) <= get_save_2(sprintf("player.%d.time", id)))
				break;
			//交换位置
			set_save_2(sprintf("biaowang.%d", i), id1);
			set_save_2(sprintf("player.%d.pos", id1), i);
			set_save_2(sprintf("biaowang.%d", i - 1), id);
			set_save_2(sprintf("player.%d.pos", id), i - 1);
		}
		save();
	}
}
//根据名次领取镖王奖励
void get_biaowang_bonus(object who, int flag)
{
	int p;
	string *nTmp, tmp;
	object item;
	if (flag == 1)
	{
		if (USER_INVENTORY_D->count_empty_carry(who) < 1)
		{
			send_user(who, "%c%s", '!', "Hành trang không đủ 1 ô trống");
			return 0;
		}
		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(), who->get_gender(), who->get_level(), HEAD_TYPE + random(6));
		tmp = nTmp[random(sizeof(nTmp))];
		if (!stringp(tmp))
			return;
		item = new (tmp);
		item->set_record(1);
		ITEM_EQUIP_D->init_equip_prop_3(item);
		p = item->move(who, -1);
		item->add_to_user(p);
		who->add_cash(200000);
		who->add_title("A006");
		send_user(who, "%c%s", ';', sprintf("Bạn nhận được phần thưởng 1 danh hiệu, 200000 lượng, %s", item->get_name()));
	}
	else if (flag == 2)
	{
		if (USER_INVENTORY_D->count_empty_carry(who) < 1)
		{
			send_user(who, "%c%s", '!', "Hành trang không đủ 1 ô trống");
			return 0;
		}
		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(), who->get_gender(), who->get_level(), HEAD_TYPE + random(6));
		tmp = nTmp[random(sizeof(nTmp))];
		if (!stringp(tmp))
			return;
		item = new (tmp);
		item->set_record(1);
		ITEM_EQUIP_D->init_equip_prop_3(item);
		p = item->move(who, -1);
		item->add_to_user(p);
		send_user(who, "%c%s", ';', sprintf("Bạn được thưởng: %s", item->get_name()));
	}
	else if (flag == 3)
	{
		who->add_cash(200000);
		send_user(who, "%c%s", ';', "Bạn được thưởng: 200000 lượng");
	}
	else if (flag > 3 && flag <= 10)
	{
		if (USER_INVENTORY_D->count_empty_carry(who) < 1)
		{
			send_user(who, "%c%s", '!', "Hành trang không đủ 1 ô trống");
			return 0;
		}
		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(), who->get_gender(), who->get_level(), HEAD_TYPE + random(6));
		tmp = nTmp[random(sizeof(nTmp))];
		if (!stringp(tmp))
			return;
		item = new (tmp);
		item->set_record(1);
		ITEM_EQUIP_D->init_equip_prop_1(item);
		p = item->move(who, -1);
		item->add_to_user(p);
		send_user(who, "%c%s", ';', sprintf("Bạn được thưởng: %s", item->get_name()));
	}
	set_save_2(sprintf("player.%d.bonus", who->get_number()), 1);
	log_file("biaowang.txt", sprintf("%s %s(%d) nhận %d phần thưởng\n", short_time(), who->get_name(), who->get_number(), flag));
	save();
}

void biaowang(object me, object who, int flag)
{
	int level, z, p, x1, y1, x0, y0, iTime, gold, pos;
	object npc;
	string cmd = "", tmp = "";
	int i, id, iuse;
	string *npc_info;
	mixed mxTmp;

	restore();
	switch (flag)
	{
	case 11:
		if (time() < iStart1 || time() > iFinish3)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    Hiện tại không phải thời gian hoạt động !\n" ESC "Rời khỏi", me->get_name()));
			return;
		}

		if (check_before_quest(who, me, 0, 0) != 1)
			return;
		level = who->get_level();
		if (level < 30)
		{
			send_user(who, "%c%s", '!', "Cấp bậc không đủ 30");
			return;
		}
		id = getoid(me);
		if (time() > iFinish1)
		{
			mxTmp = localtime(iFinish2);

			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
					  sprintf("Đang tiến hành Phiêu Vương Bá Chiến, hôm nay hoạt động chấm dứt,đã tiếp nhận nhiệm vụ rồi"
							  "Có thể tiếp tục hoàn thành, nhưng không có thành tích, %d:%d sẽcấp ra hôm nay"
							  "Hãy chờ đợi\n" ESC "Kiểm tra thành tích\n" +
								  sprintf("talk %x# welcome.15\n", id) + ESC "Rời khỏi",
							  mxTmp[TIME_HOUR],
							  mxTmp[TIME_MIN]));
			break;
		}
		else
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(),
					  sprintf("%s:\n   Tốc độ cùng vận khí cạnh tranh, trí tuệ cùng kỹ thuật so đấu! Hoan nghênh ngươi tham gia"
							  "Chén Phiêu Vương Bá Chiến, thưởng lớn đang vẫy gọi ngươi, vinh dự sẽ luôn xoay quanh ngươi! Có phải là thật hay không"
							  "Có thử qua mới biết được.\n   Ngươi chỉ cần mau chóng đem tiêu vương nhỏ đưa đến chỗ %s %s, sẽ có thể thu hoạch được phần thưởng"
							  "Thành thời gian càng ngắn ban thưởng càng phong phú, nằm trong top 3 còn có phần thưởng bất ngờ đang chờ đợi người!\n   Ngươi chuẩn bị xong chưa?"
							  "\n" ESC "Bắt đầu hộ tống \ntalk %x# welcome.12\n" ESC "Thành tích thẩm tra \n" +
								  sprintf("talk %x# welcome.15\n", id) + ESC "Rời khỏi",
							  me->get_name(), npc_num[num][0], npc_num[num][1], getoid(me)));
		}
		break;
	case 12:
		if (time() < iStart1 || time() > iFinish1)
			return;
		if (check_before_quest(who, me, 0, 0) != 1)
			return;
		if (who->get_online_rate() != 100)
		{
			send_user(who, "%c%s", '!', "Ngươi bây giờ không được khỏe mạnh, không thể tham gia hoạt động!");
			return;
		}
		level = who->get_level();
		if (level < 30)
		{
			send_user(who, "%c%s", '!', "Đẳng cấp của ngươi không đủ 30 Cấp");
			return;
		}
		npc = new ("/npc/task/8100");
		npc->set_name(sprintf("Tiêu vương nhỏ siêu nhân (%d)", who->get_number()));
		npc->set_walk_speed(3);
		z = get_z(who);
		x0 = get_x(who);
		y0 = get_y(who);
		if (p = get_valid_xy(z, x0, y0, IS_CHAR_BLOCK))
		{
			x1 = p / 1000;
			y1 = p % 1000;
			npc->add_to_scene(z, x1, y1, get_front_xy(x1, y1, x0, y0));
			npc->set_owner(who);
			who->to_front_xy(x1, y1);
		}

		who->set_quest("escort.escort", sprintf("%x#", getoid(npc)));
		who->set_quest("escort.npc", npc);

		who->delete_quest("escort.id");
		who->delete_quest("escort.random"); // 记录随机事件
		who->delete_quest("escort.robber");
		who->delete_quest("escort.robber#");
		who->delete_quest("escort.member");
		who->set_quest("escort.leader", 1);
		who->set_quest("escort.biaowang", 1);
		who->set_quest("escort.time", time());
		who->set_quest("escort.flag", 3);
		who->set_quest("escort.name", "Triệu Mục");
		who->set_quest("escort.npcname", "Tiêu vương nhỏ siêu nhân");
		who->set_quest("escort.npcinfo", npc_num[num]);
		send_task_list(who);
		break;
	case 13: //领取奖励
		iTime = time();
		if (iTime < iFinish1 || iTime > iFinish3)
			return;
		if (iTime >= iFinish1 && iTime <= iFinish2)
		{
			send_user(who, "%c%s", '!', "Năm nay Phiêu Vương Bá Chiến Cuối cùng lấy được thưởng người chơi còn không có xác định, mời kiên nhẫn chờ!");
			return;
		}
		if (get_save_2(sprintf("player.%d.bonus", who->get_number())))
		{
			send_user(who, "%c%s", '!', "Ngươi đã từng lĩnh thưởng!");
			return;
		}
		pos = get_save_2(sprintf("player.%d.pos", who->get_number()));
		if (pos >= 1 && pos <= 10)
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    Ai nha, ngươi chính là Phiêu Vương Bá Chiến Đoạt giải nhất năm nay hay sao? Đây là đưa cho ngươi phần thưởng!\n" ESC "Thu hoạch được phần thưởng \ntalk %x# welcome.14\n" ESC "Rời khỏi", me->get_name(), getoid(me)));
		else
		{
			send_user(who, "%c%s", '!', "Ngươi dường không phải tiêu vương.");
			return;
		}
		break;
	case 14: //领取奖励
		iTime = time();
		if (iTime < iFinish1 || iTime > iFinish3)
			return;
		if (iTime >= iFinish1 && iTime <= iFinish2)
		{
			send_user(who, "%c%s", '!', "Năm nay Phiêu Vương Bá Chiến Cuối cùng lấy được thưởng người chơi còn không có xác định, mời kiên nhẫn chờ!");
			return;
		}
		if (get_save_2(sprintf("player.%d.bonus", who->get_number())))
		{
			send_user(who, "%c%s", '!', "Ngươi đã từng lĩnh thưởng");
			return;
		}
		pos = get_save_2(sprintf("player.%d.pos", who->get_number()));
		if (pos < 1 || pos > 10)
		{
			send_user(who, "%c%s", '!', "Ngươi dường không phải tiêu vương.");
			return;
		}
		if (pos >= 1 && pos <= 10)
		{
			get_biaowang_bonus(who, pos);
		}
		break;
	case 15:
		for (i = 1; i <= 10; i++)
		{
			id = get_save_2(sprintf("biaowang.%d", i));
			if (!id)
			{
				tmp = sprintf("%2d.%21s", i, "Chỗ trống");
			}
			else
			{
				iuse = get_save_2(sprintf("player.%d.time", id));
				tmp = sprintf("%2d.%-13s" HIR "%02d Phút %02d Giây" NOR, i, get_save_2(sprintf("player.%d.name", id)) + ":", iuse / 60, iuse % 60);
			}
			if ((i - 1) % 2)
				tmp += "\n";
			else
				tmp += "\t\t\t\t\t";
			cmd += tmp;
		}
		send_user(who, "%c%s", ':', "Lần này tranh tài xếp hạng" + ":\n" + cmd + ESC "Rời khỏi\nCLOSE\n");
		break;
	case 21:
		npc_info = who->get_quest("escort.npcinfo");
		if (!(who->get_quest("escort.biaowang") && arrayp(npc_info) &&
			  npc_info[1] == me->get_name()))
			return;
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n   Ngươi chính là dự bị tranh đoạt tiêu vương sao? Để chúng ta xem thử!\n" ESC "Hoàn thành nhiệm vụ\ntalk %x# welcome.22\n" ESC "Rời khỏi", me->get_name(), getoid(me)));
		break;
	case 22:
		npc_info = who->get_quest("escort.npcinfo");
		if (!(who->get_quest("escort.biaowang") && arrayp(npc_info) &&
			  npc_info[1] == me->get_name()))
			return;
		iTime = gone_time(who->get_quest("escort.time"));
		if (iTime > 2400)
		{
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n   Ngươi tới quá muộn, không thể tham gia trận đấu, hãy hủy bỏ nhiệm vụ!\n" ESC "Rời khỏi", me->get_name()));
			return;
		}
		npc = who->get_quest("escort.npc");
		if (npc)
		{
			if (!inside_screen_2(me, npc))
			{
				send_user(who, "%c%s", '!', "Người ngươi muốn hộ tống đâu?!");
				return;
			}
			npc->remove_from_scene();
			destruct(npc);
		}
		else
		{
			send_user(who, "%c%s", '!', "Người ngươi muốn hộ tống đâu?!");
			return;
		}
		send_user(who, "%c%c%d%w%w", 0x54, 12, getoid(who), -1, -1); // 借用 getoid(who)
		who->set_task_xy(0);
		check_biaowang(me, who, iTime);
		clear_task(who);

		if (iTime < 180)
			gold = 55000;
		else if (iTime < 240)
			gold = 45000;
		else
			gold = 30000;
		who->add_cash(gold);
		who->add_log("$biaowang", gold);
		send_user(who, "%c%s", ';', sprintf("Ngài tham dự Phiêu Vương Bá Chiến, tiền tài %+d.", gold));
		send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_ESCORT, 3, "");
		log_file("biaowang.txt", sprintf("%s %s(%d) Hoàn thành %d Giây \n", short_time(), who->get_name(), who->get_number(), iTime));
		break;
	}
}

int set_game_flag(int i)
{
	iFlag = i;
	save();
	return i;
}

void check_time()
{
	int iTime, i, id, iUse, call_time;
	mixed mxTmp;
	string cTmp;

	remove_call_out("check_time");
	iTime = time();
	if (iTime > iFinish3 && !iFlag)
		return;
	if (iTime < iStart1)
	{
		if ((i = iStart1 - iTime) <= 600)
		{
			CHAT_D->sys_channel(0, sprintf(HIY "Thứ %d Giới nhỏ siêu nhân chén Phiêu Vương Bá Chiến%d Phút sau sẽ bắt đầu! Đây là nơi cạnh tranh khá gay gắt, trí tuệ cùng kỹ thuật so đấu! Thưởng lớn đang chờ gọi ngươi, vinh dự đang ở xung quanh, ai mới là Chiến quốc tiêu vương, chỉ có thử qua mới biết được! Nhanh đến Uất Trì lão tiêu đầu đợi hoạt động bắt đầu đi!", iGame + 1, (iStart1 - iTime) / 60));
			if (i > 120)
				i = 120;
			call_out("check_time", i);
		}
		else
			call_out("check_time", i - 600);
		return;
	}
	if (iTime >= iStart1 && iTime < iFinish1 && !iFlag)
		iFlag = 1;
	if (iFlag)
	{
		if (iTime >= iFinish1 && iTime <= iFinish2 && iFlag == 2)
			set_game_flag(3);
		else if (iTime >= iFinish2 && iTime <= iFinish3 && iFlag == 4)
			set_game_flag(5);
		else if (iTime >= iFinish3 && iFlag == 6)
			set_game_flag(7);
	}
	if (iTime < iFinish1)
	{
		call_time = iFinish1 - iTime;
		if (call_time > 300)
			call_time = 300;
	}
	else if (iTime < iFinish2)
		call_time = iFinish2 - iTime;
	else if (iTime < iFinish3)
		call_time = iFinish3 - iTime;
	else
		call_time = 0;
	if (call_time)
		call_out("check_time", call_time);

	if (iFlag == 1)
	{
		delete_save_2("biaowang");
		delete_save_2("player");
		iFlag = 2;
		iGame++;
		CHAT_D->sys_channel(0, sprintf(HIY "Thứ %d Giới nhỏ siêu nhân chén Phiêu Vương Bá Chiến%d Phút sau sẽ bắt đầu! Đây là nơi cạnh tranh khá gay gắt, trí tuệ cùng kỹ thuật so đấu! Thưởng lớn đang chờ gọi ngươi, vinh dự đang ở xung quanh, ai mới là Chiến quốc tiêu vương, chỉ có thử qua mới biết được! Nhanh đến Uất Trì lão tiêu đầu để tranh đoạt đi!", iGame));
		save();
		return;
	}
	else if (iFlag == 2)
	{
		CHAT_D->sys_channel(0, HIY "Chén Phiêu Vương Bá Chiến năm nay, hoạt động trước mắt xếp hạng trước ba tiêu vương  hữu lực tranh đoạt là:");
		for (i = 1; i <= 3; i++)
		{
			id = get_save_2(sprintf("biaowang.%d", i));
			if (!id)
			{
				CHAT_D->sys_channel(0, sprintf(HIY "Chỗ trống thứ %d", i));
				continue;
			}
			iUse = get_save_2(sprintf("player.%d.time", id));
			CHAT_D->sys_channel(0, sprintf(HIY "Thứ %d" HIR "%s" HIY ", thời gian sử dụng" HIR "%d Phút %d Giây", i, get_save_2(sprintf("player.%d.name", id)), iUse / 60, iUse % 60));
		}
		return;
	}
	else if (iFlag == 3)
	{
		for (i = 1; i <= 3; i++)
		{
			id = get_save_2(sprintf("biaowang.%d", i));
			if (!id)
			{
				continue;
			}
			iUse = get_save_2(sprintf("player.%d.time", id));
			log_file("biaowang.txt", sprintf("%s Thứ %d Giới Phiêu Vương Bá Chiến Thứ %d Tên %s(%d) %s Thời gian sử dụng %d Phút %d Giây \n", short_time(), iGame, i, get_save_2(sprintf("player.%d.name", id)), id, get_save_2(sprintf("player.%d.account", id)), iUse / 60, iUse % 60));
		}
		mxTmp = localtime(iFinish2);
		CHAT_D->sys_channel(0, sprintf(HIY "Năm nay nhỏ siêu nhân chén Phiêu vương báchiến Hôm nay hoạt động đến đây là kết thúc, đã tiếp nhận nhiệm vụ người chơi có thể tiếp tục hoàn thành, nhưng thành tích sẽ không tiến nhập tiêu vương xếp hạng tính toán, %d:%d Sẽ cho ra hôm nay Phiêu vương báchiến Kết quả, xin mọi người rửa mắt mà đợi.", mxTmp[TIME_HOUR], mxTmp[TIME_MIN]));
		set_game_flag(4);
		return;
	}
	else if (iFlag == 5) //公布得奖名单
	{
		CHAT_D->sys_channel(0, HIY "Năm nay Chén Phiêu Vương Bá Chiến trong hoạt động tiêu vương đã sinh ra, bọn hắn là:");
		for (i = 1; i <= 10; i++)
		{
			id = get_save_2(sprintf("biaowang.%d", i));

			if (i <= 3)
			{
				if (!id)
				{
					CHAT_D->sys_channel(0, sprintf(HIY "Chỗ trống thứ %d", i));
					continue;
				}
				cTmp = i == 1 ? "Tiêu Vương" : (i == 2 ? "Á Quân" : "Quý Quân");
				iUse = get_save_2(sprintf("player.%d.time", id));
				CHAT_D->sys_channel(0, sprintf(HIY "%s" HIR "%s" HIY ", thời gian sử dụng" HIR "%d Phút %d Giây", cTmp, get_save_2(sprintf("player.%d.name", id)), iUse / 60, iUse % 60));
				MAILBOX->sys_mail(get_save_2(sprintf("player.%d.account", id)), id, "Chúc mừng ngài! Đã dành được Chén Phiêu Vương Bá Chiến năm nay" + HIR + cTmp + NOR + "Ban thưởng, xin mau chóng tới Chu Quốc tìm Uất Trì lão tiêu đầu nhận thưởng! Vượt qua 12h đêm nay sẽ bị coi là tự từ bỏ ban thưởng.");
			}
			else
				MAILBOX->sys_mail(get_save_2(sprintf("player.%d.account", id)), id, "Chúc mừng ngài! Đã dành được Chén Phiêu Vương Bá Chiến năm nay, xin mau chóng tới Chu Quốc tìm Uất Trì lão tiêu đầu nhận thưởng! Vượt qua 12h đêm nay sẽ bị coi là tự từ bỏ ban thưởng.");
		}
		CHAT_D->sys_channel(0, HIY "Hãy nhận thưởng vào lúc 23:59 ở Uất Trì lão tiêu đầu. Vượt qua 23:59 mà không đi nhận thưởng, sẽ bị coi như tự từ bỏ.");
		set_game_flag(6);
		return;
	}
	else if (iFlag == 7)
	{
		for (i = 1; i <= 3; i++)
		{
			id = get_save_2(sprintf("biaowang.%d", i));
			if (!id)
				continue;
			iUse = get_save_2(sprintf("player.%d.bonus", id));
			if (!iUse)
			{
				cTmp = i == 1 ? "Tiêu Vương" : (i == 2 ? "Á Quân" : "Quý Quân");
				log_file("biaowang.txt", sprintf("%s %s(%d) Quá thời gian nhận thưởng \n", short_time(), get_save_2(sprintf("player.%d.name", id)), id, ));
				MAILBOX->sys_mail(get_save_2(sprintf("player.%d.account", id)), id, "Thật đáng tiếc, mặc dù ngài thu được Chén Phiêu Vương Bá Chiến" + cTmp + " Vượt qua 23:59 mà không đi nhận thưởng, sẽ bị coi như tự từ bỏ. Hãy nhớ kỹ thời gian");
			}
		}
		delete_save_2("biaowang");
		delete_save_2("player");
		iStart1 += 3600 * 24 * 7; //一星期后活动开启
		iFinish1 += 3600 * 24 * 7;
		iFinish2 += 3600 * 24 * 7;
		iFinish3 += 3600 * 24 * 7;
		iFlag = 0;
		call_out("check_time", 3);
		num++;
		if (num >= 4)
			num = 0; //循环4个路径
		save();
		return;
	}
}

int set_open(object who, string arg)
{
	int year, mon, day, hour, min;
	string cTmp1, cTmp2, cTmp3;
	if (sscanf(arg, "%s-%s-%s", cTmp1, cTmp2, cTmp3) != 3)
	{
		send_user(who, "%c%s", '!', "Sai cách thức!");
		return 0;
	}
	//20070518 2000
	year = to_int(cTmp1[0..3]);
	mon = to_int(cTmp1[4..5]);
	day = to_int(cTmp1[6..7]);
	hour = to_int(cTmp1[8..9]);
	min = to_int(cTmp1[10..11]);
	iStart1 = mktime(year, mon, day, hour, min, 0); //活动开始时间

	year = to_int(cTmp2[0..3]);
	mon = to_int(cTmp2[4..5]);
	day = to_int(cTmp2[6..7]);
	hour = to_int(cTmp2[8..9]);
	min = to_int(cTmp2[10..11]);
	iFinish1 = mktime(year, mon, day, hour, min, 0); //结束时间

	year = to_int(cTmp3[0..3]);
	mon = to_int(cTmp3[4..5]);
	day = to_int(cTmp3[6..7]);
	hour = to_int(cTmp3[8..9]);
	min = to_int(cTmp3[10..11]);
	iFinish2 = mktime(year, mon, day, hour, min, 0); //发奖时间
	iFinish3 = mktime(year, mon, day + 1, 0, 0, 0);	 //发奖结束时间

	if (!iStart1 || !iFinish1 || !iFinish2)
	{
		send_user(who, "%c%s", '!', "Sai thời gian!");
		return 0;
	}
	if (iStart1 > iFinish1 || iFinish1 < time() || iFinish1 > iFinish2)
	{
		send_user(who, "%c%s", '!', "Sai thời gian!!");
		return 0;
	}
	tell_user(who, "Phiêu Vương Bá Chiến mở ra:%s!", arg);
	send_user(who, "%c%s", '!', "Phiêu Vương Bá Chiến mở ra!");
	iFlag = 0;
	save();
	call_out("check_time", 3);
	return 1;
}

int set_close(object who)
{
	remove_call_out("check_time");
	iStart1 = 0;
	iFinish1 = 0;
	iFinish2 = 0;
	iFinish3 = 0;
	iFlag = 0;
	num = 0;
	send_user(who, "%c%s", '!', "Phiêu Vương Bá Chiến đóng lại!");
	save();
	return 1;
}

int test(int i)
{
	if (i == 1)
	{
		iStart1 = time() + 610;
		iFinish1 = time() + 1800;
		iFinish2 = time() + 1830;
		iFinish3 = time() + 1840;
		iFlag = 0;
		save();
	}
	else if (i == 2)
	{
		iStart1 = time() + 10;
		iFinish1 = time() + 1800;
		iFinish2 = time() + 1830;
		iFinish3 = time() + 1840;
		iFlag = 0;
		save();
	}
	else if (i == 3)
	{
		iStart1 = time() - 10;
		iFinish1 = time() - 5;
		iFinish2 = time() + 1830;
		iFinish3 = time() + 1840;
		//		iFlag = 3;
		save();
	}
	else if (i == 4)
	{
		iStart1 = time() - 20;
		iFinish1 = time() - 10;
		iFinish2 = time() - 5;
		iFinish3 = time() + 1840;
		//		iFlag = 4;
		save();
	}
	else if (i == 5)
	{
		iStart1 = time() - 20;
		iFinish1 = time() - 10;
		iFinish2 = time() - 5;
		iFinish3 = time() - 2;
		//		iFlag = 5;
		save();
	}
	check_time();
}
