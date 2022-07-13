//武林败类头目NPC
#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <skill.h>
#include <effect.h>
#include <action.h>

inherit NPC;

int hptime;
int summon_slave(object me);
//void outlet(int sec,object map);
int *nScene = ({289, 273, 80, 324, 269, 54, 165});
string *nFamily = ({"Đào Hoa Nguyên", "Thục Sơn", "Cấm Vệ Quân", "Đường Môn", "Mao Sơn", "Côn Luân Sơn", "Vân Mộng Cốc"});
// 函数：是否不能进城
int cannot_enter_city() { return 1; }

// 函数：构造处理
void create()
{
	set_name("Thủ Lĩnh Võ Lâm Bại Hoại");
	//        set_char_picid(9415);    // 蒙面人
	setup();
}

// 函数：获取装备代码
int get_weapon_code() { return UNARMED; }

// --------------------------------------------------------------- 远程调用 ----

int can_fight(object who)
{
	if (!get_map_object(get_z(who))->is_scum_map())
		return 0;
	return 1;
}

// 函数：死亡奖励
void win_bonus(object who) { __FILE__->win_bonus_callout(this_object(), who); }

// 函数：死亡奖励(在线更新)
void win_bonus_callout(object me, object who)
{
	object item, leader, map, *member, npc1;
	string file, owner, id;
	int p, rate, i, size, gold, equip, rate1, tId, level, exp;
	int z, x, y;
	string *nTmp;

	tId = me->get("team_id");
	//	name = npc->get_name();
	//	map = TEAM_D->get_copy_scene(tId,COPY_SCUM);
	map = get_map_object(get_z(me));
	if (!map)
		return;
	//奖励经验
	// exp = 1000 + random(501);
	// if (!who->get_team_id())
	// 	who->add_exp(exp * (who->get_online_rate() / 100));
	// else
	// {
	// 	member = who->get_team();
	// 	member -= ({0});
	// 	for (i = 0, size = sizeof(member); i < size; i++)
	// 	{
	// 		member[i]->add_exp(exp * (member[i]->get_online_rate() / 100));
	// 		//			member[i]->add_save("testbonus",10);
	// 	}
	// }

	//掉物品
	z = get_z(me);
	x = get_x(me);
	y = get_y(me);
	id = who->get_leader();
	level = map->get("copy_level");
	member = "tran/phuban/map"->get_all_user(map);
	if (!id)
		owner = who->get_id();
	else
	{
		if (leader = find_player(id))
		{
			owner = leader->get_id();
		}
		else
			owner = who->get_id();
	}
	//rate1 = me->correct_drop_rate(me->get_level() - who->get_level()) * who->get_online_rate() / 100;
	p = get_valid_xy(z, x, y, IS_ITEM_BLOCK);
	if (!p)
		return;
	rate = random(100);
	rate1 = level / 10;
	if (level == 100) //Gốc là boss lv 100 thì ra boss
	{
		// for (i = 0; i < 3; i++)
		// {
		// 	if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)) //随机宠物技能书
		// 	{
		// 		item = new ("item/tuilinhthach/ngaunhien/7");
		// 		if (item)
		// 		{
		// 			TEAM_D->drop_item(item, who);
		// 			item->set_user_id(owner);
		// 			item->add_to_scene(z, p / 1000, p % 1000);
		// 			item->set("winner", who);
		// 			item->set("time", time());
		// 		}
		// 	}
		// }

		// if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)) //随机宠物技能书
		// {
		// 	item = new ("item/sell/4032");
		// 	if (item)
		// 	{
		// 		TEAM_D->drop_item(item, who);
		// 		item->set_user_id(owner);
		// 		item->add_to_scene(z, p / 1000, p % 1000);
		// 		item->set("winner", who);
		// 		item->set("time", time());
		// 	}
		// }
	}
	if (level >= 50)
	{
		// if (rate < 40 + rate1)
		// {
		// 	if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
		// 	{
		// 		item = new ("/item/sell/5032");

		// 		TEAM_D->drop_item(item, who);
		// 		item->set_user_id(owner);
		// 		item->add_to_scene(z, p / 1000, p % 1000);
		// 		item->set("winner", who);
		// 		item->set("time", time());
		// 	}
		// }
		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
		{
			item = new ("/item/tuilinhthach/ngaunhien/2");

			TEAM_D->drop_item(item, who);
			item->set_user_id(owner);
			item->add_to_scene(z, p / 1000, p % 1000);
			item->set("winner", who);
			item->set("time", time());
		}
		if (rate < 40 + rate1)
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				item = new ("/item/tuilinhthach/ngaunhien/3");

				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
		if (rate < 20 + rate1)
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				item = new ("/item/tuilinhthach/ngaunhien/4");

				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
	}
	for (i = 0; i < random(5) + rate1; i++)
	{
		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
		{
			item = new ("/item/test/TuiDT");
			if (!item)
				continue;
			TEAM_D->drop_item(item, who);
			item->set_user_id(owner);
			item->add_to_scene(z, p / 1000, p % 1000);
			item->set("winner", who);
			item->set("time", time());
		}
	}
	for (i = 0; i < random(5) + rate1; i++)
	{
		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
		{
			item = new ("/item/test2/tuilinhthach");
			if (!item)
				continue;
			TEAM_D->drop_item(item, who);
			item->set_user_id(owner);
			item->add_to_scene(z, p / 1000, p % 1000);
			item->set("winner", who);
			item->set("time", time());
		}
	}
	// for (i = 0; i < random(5) + rate1; i++)
	// {
	// 	if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
	// 	{
	// 		item = new ("/item/huyenthu/exp");
	// 		if (!item)
	// 			continue;
	// 		TEAM_D->drop_item(item, who);
	// 		item->set_user_id(owner);
	// 		item->add_to_scene(z, p / 1000, p % 1000);
	// 		item->set("winner", who);
	// 		item->set("time", time());
	// 	}
	// }
	for (i = 0; i < random(5) + rate1; i++)
	{
		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
		{
			item = new (BOOK_FILE->get_book_file());
			TEAM_D->drop_item(item, who);
			item->set_user_id(owner);
			item->add_to_scene(z, p / 1000, p % 1000);
			item->set("winner", who);
			item->set("time", time());
		}
	}
	for (i = 0; i < random(10) + rate1; i++)
	{
		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
		{
			item = new ("/item/91/9167");
			if (!item)
				continue;
			TEAM_D->drop_item(item, who);
			item->set_user_id(owner);
			item->add_to_scene(z, p / 1000, p % 1000);
			item->set("winner", who);
			item->set("time", time());
		}
	}
	for (i = 0; i < random(10) + rate1; i++) //5堆5000金
	{
		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
		{
			item = new ("/item/std/0001");
			item->set_value(50000);
			TEAM_D->drop_item(item, who);
			item->set_user_id(owner);
			item->add_to_scene(z, p / 1000, p % 1000);
			item->set("winner", who);
			item->set("time", time());
		}
	}
	if (level == 100)
	{
		"tran/phuban/go"->outlet(60, map);
		return;
	}
	else
	{
		map->add("copy_level", 1);
		map->add("copy_npc_amount", 2000); // Gốc 10000
		"tran/phuban/creep"->generate_copy_npc(tId, map->get_id(), map->get("copy_level"));
		for (i = 0; i < sizeof(member); i++)
		{
			if (get_z(member[i]) != z)
				continue;
			send_user(member[i], "%c%s", ';', sprintf(HIY "BOSS %d Đã Bị Tiêu Diệt", map->get("copy_npc_amount") / 2000 - 1));	 // Gốc 10000 - 1
			send_user(member[i], "%c%c%s", 0xA5, 1, sprintf("| TIẾN TỚI TẦNG %d - ĐỢT 11", map->get("copy_npc_amount") / 2000)); //Gốc 10000
		}
	}
}

// 函数：特技攻击对手
int perform_action(object who)
{
	int rate;
	object me = this_object();

	if (get_z(who) != get_z(me) || !inside_screen_2(me, who))
		return 0;
	rate = random(100);
	switch (me->get("scum.type"))
	{
	case 1:
		if (rate < 5)
			return PF_FILE_03483->perform_action_npc(me, who);
		else if (rate < 17)
			return PF_FILE_02512->perform_action_npc(me, who);
		else if (rate < 20)
			return PF_FILE_02416->perform_action_npc(me, who);
		break;
	case 2:
		if (rate < 8)
			return PF_FILE_02216->perform_action_npc(me, who);
		else if (rate < 16)
			return PF_FILE_02313->perform_action_npc(me, who);
		else if (rate < 24)
			return PF_FILE_02314->perform_action_npc(me, who);
		break;
	case 3:
		// 封
		if (get_effect(me, EFFECT_CHAR_NO_PF))
			return 0;
		if (get_effect(me, EFFECT_CHAR_CHANGE) < 1)
		{
			PF_FILE_04251->cast_done_npc(me);
		}
		if (rate < 70)
			return PF_FILE_04231->perform_action_npc(me, who);
		else if (rate < 90)
			return PF_FILE_04232->perform_action_npc(me, who);
		else if (rate < 97)
			return PF_FILE_04234->perform_action_npc(me, who);
		else
			return PF_FILE_04243->perform_action_npc(me, who);
		break;
	case 4:
		if (!me->get_perform("03173"))
		{
			PF_FILE_03173->perform_action_npc(me, who);
		}
		if (rate < 5)
			return PF_FILE_02118->perform_action_npc(me, who);
		else if (rate < 13)
			return PF_FILE_02114->perform_action_npc(me, who);
		else if (rate < 25)
			return PF_FILE_02115->perform_action_npc(me, who);
		break;
	case 5:
		if (!me->get_effect(me, EFFECT_USER_HURT))
		{
			PF_FILE_03632->cast_done_npc(me);
		}
		if (rate < 10)
			return PF_FILE_02616->perform_action_npc(me, who);
		else if (rate < 20)
			return PF_FILE_02615->perform_action_npc(me, who);
		break;
	case 6:
		// 封
		summon_slave(me);
		if (get_effect(me, EFFECT_CHAR_NO_PF))
			return 0;
		if (rate < 6)
			return PF_FILE_04143->perform_action_npc(me, who);
		else if (rate < 12)
			return PF_FILE_04144->perform_action_npc(me, who);
		else if (rate < 15)
			return PF_FILE_04145->perform_action_npc(me, who);
		break;
	default:
		break;
	}
	return 0;
}

//自动跟踪玩家
void heart_beat_walk()
{
	string robber;
	object *member, who, owner;
	object me = this_object(), enemy;
	int x, y, z, x0, y0, z0, x1, y1, p, i;

	if (gone_time(hptime) >= 20 + random(21))
	{
		hptime = time();
		//瞬间移动
		enemy = get_enemy();
		if (objectp(enemy))
		{
			z = get_z(enemy);
			z0 = get_z(me);

			if (z == z0 && distance_between(me, enemy) < 20)
			{
				x = get_x(enemy);
				y = get_y(enemy);
				x0 = get_x(me);
				y0 = get_y(me);
				for (i = 0; i < 10; i++)
				{
					if (p = get_valid_xy(z, abs(x + random(3) - 1), abs(y + random(3) - 1), IS_CHAR_BLOCK))
					{
						x1 = p / 1000;
						y1 = p % 1000;
						break;
					}
				}
				if (x1 && y1 && z && !MAP_D->is_inside_city(z, x1, y1))
				{
					send_user(get_scene_object_2(me, USER_TYPE), "%c%w%w%w%c%c%c", 0x4f, x0, y0, 9413, 1, OVER_BODY, PF_ONCE); // 补发指令
					me->add_to_scene(z, x1, y1);
					me->to_front_xy(x, y);
				}
			}
		}
	}
	member = get_range_object_2(me, me->get_max_seek(), CHAR_TYPE) + get_range_object_2(me, me->get_max_seek(), USER_TYPE) - ({me});
	if (sizeof(member) != 0)
	{
		foreach (who in member)
		{
			if (who->is_die())
				continue;
			if (me->can_fight(who) != 1)
				continue;
			me->set_main_enemy(who);
			::heart_beat_walk();
			return;
		}
	}
	owner = me->get_enemy();
	if (!objectp(owner))
		return;
	if (get_z(owner) != get_z(me) || distance_between(me, owner) > 20)
	{
		me->set_enemy(0);
		return;
	}
}

void heart_beat_attack()
{
	string robber;
	object who;
	object me = this_object();

	who = me->get_enemy();
	if (!objectp(who))
		return;
	if (get_z(who) != get_z(me) || distance_between(me, who) > 20 || !who->can_fight(me))
	{
		me->set_enemy(0);
		return;
	}
	::heart_beat_attack();
}

//召唤
int summon_slave(object me)
{
	object npc;
	string arg;
	int z, x, y, x0, y0, p;
	int level, cp, pp, i, size;
	if (me->get("robber.slave") >= 5)
		return 0;
	level = me->get_level() - 15;
	z = get_z(me);
	x0 = get_x(me);
	y0 = get_y(me);

	if (p = get_valid_xy(z, x0 + random(3) - 1, y0 + random(3) - 1, IS_CHAR_BLOCK))
	{

		npc = new ("/npc/party/scum_summon2");
		if (!objectp(npc))
			return;

		NPC_ENERGY_D->init_level(npc, level);
		if (random(2))
			npc->set_char_picid(52);
		else
			npc->set_char_picid(201);
		npc->set_walk_speed(6);
		npc->set_attack_speed(15);
		npc->set_max_seek(8);

		npc->add_max_hp(100); // 小心准备 me
		npc->add_hp(100);
		npc->add_dp(level);
		npc->add_pp(level);

		npc->set_owner(me);

		//		npc->set_char_type(FIGHTER_TYPE);

		x = p / 1000;
		y = p % 1000;
		npc->add_to_scene(z, x, y, get_front_xy(x, y, x0, y0));
		send_user(get_scene_object_2(npc, USER_TYPE), "%c%d%w%c%c%w%c%c%w%c%c%c", 0x6f, getoid(npc),
				  41311, 1, OVER_BODY, 41312, 1, OVER_BODY, 41313, 1, UNDER_FOOT, PF_ONCE);

		me->add("robber.slave", 1);

		NPC_SLAVE_D->find_enemy(npc); // 寻找敌人
	}

	return 1; // 执行成功
}
