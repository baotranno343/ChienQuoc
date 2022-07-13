#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <effect.h>
#include <cmd.h>
#include <skill.h>
#include <task.h>
#define _DEBUG(x) tell_user(find_char("971"), x);

inherit NPC;

int flag;
int saytime, hptime, lowhp, silent, summon, RelaxTime;
string *nFamily = ({"Đào Hoa Nguyên", "Thục Sơn", "Cấm Vệ Quân", "Đường Môn", "Mao Sơn", "Côn Luân", "Vân Mộng Cốc"});
// 函数：是否不能进城
int cannot_enter_city() { return 1; }
int get_id_color() { return 0x800080; }
//int is_caster () { return 1; }
void drop_items(object me, object who);
int is_tiger_king() { return 1; }
int is_officer() { return get_char_type() == OFFICER_TYPE ? 1 : 0; }
void do_fight();
void init_fight_status()
{
	set_ap(1400);
	set_dp(950);
	set_cp(700);
	set_pp(850);
	set_sp(200);
}

// 函数：构造处理
void create()
{
	object me = this_object();
	set_name("Khuyển Thái Lang");
	set_char_picid(1230);
	set_level(40);
	set_max_hp(2500000);
	set_max_mp(500);
	init_fight_status();
	set_walk_speed(3);
	set_attack_speed(15);
	set_max_seek(8);
	set_walk_step(2);
	set("no_sk04211", 1);	//变身术对其没有效果
	set("anti_sleep", 1);	//不会昏迷
	set("anti_no_move", 1); //不会冻结

	set_skill(11004, 40);
	set_skill(0211, 40);
	set_skill(0423, 40);

	setup();
	set_char_type(OFFICER_TYPE);
	set("birthday", time());
	if (!clonep(me))
		return;
	CHAT_D->rumor_channel(0, CHAT + "Nghe nói Khuyển Thái Lang lại đi lại ở vùng khe núi Đông Lai ở Hải Tân 2 đợi khiêu chiến với dũng sĩ.");
	set_2("talk", (["fight":(
								: do_fight:),
	]));
	log_file("boss.txt", short_time() + " Khuyển Thái Lang xuất hiện\n");
}

int can_fight(object who)
{
	object owner;
	string leader, id;
	if (get_char_type() == OFFICER_TYPE)
		return 0;
	if (who->is_die())
	{
		set_enemy(0);
		return 0;
	}
	if (who->is_npc() && objectp(owner = who->get_owner()))
		who = owner;
	if (who->is_npc())
	{
		set_enemy(0);
		return 0;
	}

	return ::can_fight(who);
}

int can_be_fighted(object who)
{
	object owner;
	string leader, id;
	if (get_char_type() == OFFICER_TYPE)
		return 0;
	if (who->is_npc() && objectp(owner = who->get_owner()))
		who = owner;
	if (who->is_npc())
	{
		set_enemy(0);
		return 0;
	}
	if (who->is_user() && who->get_level() <= 40)
	{
		set_enemy(0);
		send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), "Ngươi còn bé lắm, hãy về luyện thêm võ công rồi đánh nhau với ta!");
		return 0;
	}
	return ::can_be_fighted(who);
}

void heart_beat_walk()
{
	int i, x, y, z, x0, y0, z0, p, x1, y1;
	object enemy, me = this_object();

	if (get_char_type() == OFFICER_TYPE) //普通状态
	{
		return;
	}
	enemy = get_enemy();
	if (objectp(enemy))
	{
		if (enemy->is_die())
			set_enemy(0);
		if (gone_time(saytime) >= 60)
		{
			saytime = time();
			if (random(100) < 40)
			{
				SAY_CMD->say(me, "Ta rất hiền lành!");
			}
		}
	}
	else if (RelaxTime == 0)
	{
		RelaxTime = time();
	}
	if (RelaxTime && gone_time(RelaxTime) >= 60)
	{
		RelaxTime = 0;
		set_char_type(OFFICER_TYPE);
		//		add_to_scene(14,162,98);
	}
	if (!get_effect(me, EFFECT_CHAR_NO_PF_0)) //不沉默
	{
		set_effect(me, EFFECT_CHAR_NO_PF_0, 3600);
	}
	if (!get_effect(me, EFFECT_CHAR_WOUND_0)) //不负伤
	{
		set_effect(me, EFFECT_CHAR_WOUND_0, 3600);
	}
	if (!get_effect(me, EFFECT_CHAR_FAINT_0)) //不眩晕
	{
		set_effect(me, EFFECT_CHAR_FAINT_0, 3600);
	}
	if (!get_effect(me, EFFECT_CHAR_SHUT_0)) //不囚禁
	{
		set_effect(me, EFFECT_CHAR_SHUT_0, 3600);
	}
	if (!get_effect(me, EFFECT_CHAR_DREAM_0)) //不囚禁
	{
		set_effect(me, EFFECT_CHAR_DREAM_0, 3600);
	}
	if (!get_effect(me, EFFECT_CHAR_LAZY_0)) //不延缓
	{
		set_effect(me, EFFECT_CHAR_LAZY_0, 3600);
	}
	if (gone_time(hptime) >= 15)
	{
		hptime = time();
		//瞬间移动
		if (objectp(enemy))
		{
			z = get_z(enemy);
			z0 = get_z(me);

			if (z == z0 && (p = distance_between(me, enemy)) < 20 && p > 1)
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
				if (x1 && y1 && z)
				{
					me->add_to_scene(z, x1, y1, 4, 9413);
					me->to_front_xy(x, y);
				}
			}
		}
	}
	if (objectp(enemy = get_enemy()) && random100() < 10)
	{
		PF_FILE_04233->perform_action_npc(me, enemy);
		return;
	}
	::heart_beat_walk();
}
void heart_beat_attack()
{
	if (get_char_type() == OFFICER_TYPE) //普通状态
		return;
	::heart_beat_attack();
}

// 函数：特技攻击对手
int perform_action(object who)
{
	int rate, x, y, z;
	object me = this_object();

	RelaxTime = 0;

	rate = random(100);

	if (rate < 8)
	{
		SAY_CMD->say(me, "Hây da Hây da");
		return "skill/11/11004"->perform_action_npc(me, who);
	}
	else if (rate < 18)
	{
		SAY_CMD->say(me, "Chém....chém....gió!");
		return PF_FILE_02115->perform_action_npc(me, who);
	}
	else if (rate < 28)
		return PF_FILE_04233->perform_action_npc(me, who);

	return 0;
}

// 函数：复位处理
void reset()
{
}

// --------------------------------------------------------------- 远程调用 ----

// 函数：死亡奖励
void win_bonus(object who) { __FILE__->win_bonus_callout(this_object(), who); }

// 函数：死亡奖励(在线更新)
void win_bonus_callout(object me, object who)
{
	object owner, *team;
	int level, level2, exp, exp2, pot, alllevel;
	int i, size, status, time, flag;

	log_file("boss.txt", short_time() + " Khuyển Thái Lang bị tiêu diệt\n");

	if (!objectp(who = me->get_enemy_4()))
		return;

	if (owner = who->get_owner())
		who = owner;
	if (who->is_npc())
		return;
	CHAT_D->rumor_channel(0, CHAT + "Khuyển Thái Lang đã bị " + who->get_name() + " tiêu diệt!");
	if (who->get_save_2("cantuong.status") == 1)
	{
		who->set_save_2("cantuong.ktl", 1);
		if (who->get_save_2("cantuong.count") >= 10000 &&
			who->get_save_2("cantuong.hv") >= 1 &&
			who->get_save_2("cantuong.agbd") >= 1 &&
			who->get_save_2("cantuong.uvdtq") >= 1 &&
			who->get_save_2("cantuong.ktl") >= 1)
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_CANTUONG, 1, "Tìm kiếm Thần Binh Phổ(Hoàn thành)");
		send_user(who, "%c%s", ';', "Đã tiêu diệt Khuyển Thái Lang cần cho nhiệm vụ nâng cấp Tuyệt thế thần binh !");
	}
	drop_items(me, who);

	level = me->get_level();
	if (who->get_leader() && arrayp(team = who->get_team()) && sizeof(team) > 1)
	{
		team = me->correct_bonus_team(team);
		size = sizeof(team);
	}
	else
	{
		team = ({who});
		size = 1;
	}

	alllevel = 0;
	for (i = 0; i < size; i++)
		if (team[i])
		{
			alllevel += team[i]->get_level();
		}
	if (alllevel == 0)
		alllevel = 1;
	exp = 15000;
	for (i = 0; i < size; i++)
		if (team[i])
		{
			level2 = level - team[i]->get_level();
			exp2 = exp * team[i]->get_level() / alllevel;
			exp2 = me->correct_exp_bonus(level, level2, exp2) * who->get_online_rate() / 100;

			if (exp2 < 5)
				exp2 = 5;
			team[i]->add_exp(exp2);
			team[i]->add_potential(100);
			team[i]->add_log("#dogboss", 1);
			team[i]->add_log("&dogboss", exp2);
			team[i]->add_log("*dogboss", 100);
		}
}

// 函数：掉宝奖励
void drop_items(object me, object who)
{
	int x, y, z, p, i, rate, rate1;
	string *nTmp, id, owner;
	object item, leader;

	z = get_z(me);
	x = get_x(me);
	y = get_y(me);
	id = who->get_leader();
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
	rate1 = me->correct_drop_rate(me->get_level() - who->get_level()) * who->get_online_rate() / 100;
	rate = random(100);
	if (rate < rate1)
	{
		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
		{
			nTmp = WEAPON_FILE->get_family_equip(nFamily[random(7)], 0, 40, HEAD_TYPE + random(6));
			if (sizeof(nTmp))
			{
				item = new (nTmp[random(sizeof(nTmp))]);
				if (!item)
					return;
				ITEM_EQUIP_D->init_equip_prop_1(item);
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
		for (i = 0; i < 5; i++)
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				item = new ("/item/std/0001");
				item->set_value(20000);
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
		for (i = 0; i < random(3) + 3; i++)
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				item = new ("/item/test2/tuilinhthach");
				if (!item)
					return;
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
		for (i = 0; i < random(3) + 2; i++)
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				item = new ("/item/test/tuiDT");
				if (!item)
					return;
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
		for (i = 0; i < 3; i++) //随机1级晶石5个
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				item = new (STONE_FILE->get_diamond_file());
				item->set_level(1);
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
		// for (i = 0; i < random(3); i++)
		// {
		// 	switch (random(2))
		// 	{
		// 	case 0:
		// 		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
		// 		{
		// 			item = new ("quest/product2"->get_random_level_yellow_product(117, 117));
		// 			TEAM_D->drop_item(item, who);
		// 			item->set_user_id(owner);
		// 			item->add_to_scene(z, p / 1000, p % 1000);
		// 			item->set("winner", who);
		// 			item->set("time", time());
		// 		}
		// 		break;

		// 	default:
		// 		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
		// 		{
		// 			item = new ("quest/product2"->get_random_level_yellow_neck_product(116, 116));
		// 			TEAM_D->drop_item(item, who);
		// 			item->set_user_id(owner);
		// 			item->add_to_scene(z, p / 1000, p % 1000);
		// 			item->set("winner", who);
		// 			item->set("time", time());
		// 		}
		// 		break;
		// 	}
		// }
	}
	rate = random100();
	if (rate < 10 * rate1 / 100) //门派技能书
	{
		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
		{
			item = new (BOOK_FILE->get_perform_file());
			if (!item)
				return;
			TEAM_D->drop_item(item, who);
			item->set_user_id(owner);
			item->add_to_scene(z, p / 1000, p % 1000);
			item->set("winner", who);
			item->set("time", time());
		}
	}
	p = get_valid_xy(z, x, y, IS_ITEM_BLOCK);
	if (!p)
		return;
	rate = random(10000);

	if (rate < 500 * rate1 / 100) //40级的随机门派金色装备
	{
		nTmp = WEAPON_FILE->get_family_equip(nFamily[random(7)], 0, random(2) ? 40 : 30, HEAD_TYPE + random(6));
		if (sizeof(nTmp))
		{
			item = new (nTmp[random(sizeof(nTmp))]);
			if (!item)
				return;
			ITEM_EQUIP_D->init_equip_prop_3(item);
			TEAM_D->drop_item(item, who);
			item->set_user_id(owner);
			item->add_to_scene(z, p / 1000, p % 1000);
			item->set("winner", who);
			item->set("time", time());
		}
	}
	else if (rate < 4500 * rate1 / 100) //紫参丹
	{
		for (i = 0; i < 2; i++)
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				item = new ("/item/91/9167");
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
	}
	else if (rate < 5000 * rate1 / 100) //40级随机配方两个
	{
		for (i = 0; i < 2; i++)
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				item = new ("/item/91/9167");
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
	}
	//	{暂时不开放改为紫参丹
	//	         for(i=0;i<2;i++)
	//	         {
	//	                if( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) )
	//	                {
	//	                        item = new( "/quest/product2"->get_random_level_product(40,40) );
	//				TEAM_D->drop_item(item,who);
	//				item->set_user_id(owner);
	//	                        item->add_to_scene(z, p / 1000, p % 1000);
	//	                        item->set("winner", who);
	//	                        item->set( "time", time() );
	//	                }
	//		}
	//	}
	else if (rate < 6000 * rate1 / 100) //劣质宝石矿 2个
	{
		for (i = 0; i < 2; i++)
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				item = new ("/item/91/9167");
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
	}
	//	{暂时不开放改为紫参丹
	//	         for(i=0;i<2;i++)
	//	         {
	//	                if( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) )
	//	                {
	//	                        item = new( "item/89/8990");
	//				TEAM_D->drop_item(item,who);
	//				item->set_user_id(owner);
	//	                        item->add_to_scene(z, p / 1000, p % 1000);
	//	                        item->set("winner", who);
	//	                        item->set( "time", time() );
	//	                }
	//		}
	//	}
	else if (rate < 7000 * rate1 / 100) //残缺宝石矿 2个
	{
		for (i = 0; i < 2; i++)
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				item = new ("/item/91/9167");
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
	}
	else if (rate < 7100 * rate1 / 100) //残缺宝石矿 2个
	{
		for (i = 0; i < 2; i++)
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				item = new (STONE_FILE->get_diamond_file());
				item->set_level(2);
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
	}
	else if (rate < 10000 * rate1 / 100) //随机技能进阶1本
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
	"/sys/npc/npc"->drop_ball(me, who);
}

void do_look(object who)
{
	send_user(who, "%c%c%w%s", ':', 3, 0352, "Khuyển Thái Lang:\n    Các ngươi muốn gì hử !?\n" + sprintf(ESC "Khiêu chiến\ntalk %x# fight\n", getoid(this_object())) + ESC "Rời khỏi");
}

void do_fight()
{
	object who = this_player(), me = this_object();

	if (get_char_type() != OFFICER_TYPE) //普通状态
		return;
	set_char_type(FIGHTER_TYPE_2);
	add_to_scene(get_z(me), get_x(me), get_y(me));
}
//杀死一个敌人加10000气血
void stop_fight()
{
	object enemy;
	enemy = get_enemy();
	if (enemy && enemy->get_hp() == 0)
		add_hp(10000);
	::stop_fight();
}