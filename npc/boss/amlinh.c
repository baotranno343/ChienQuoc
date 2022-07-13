#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <effect.h>
#include <cmd.h>
#include <skill.h>

#define _DEBUG(x) tell_user(find_char("971"), x);

inherit NPC;

int flag;
int saytime, hptime, lowhp, silent, summon, RelaxTime;
int leiTime;
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
	set_ap(5000);
	set_dp(2000);
	set_cp(3000);
	set_pp(2000);
	set_sp(2000);
}

// 函数：构造处理
void create()
{
	object me = this_object();
	set_name("Âm Linh Đạo Trưởng");
	set_char_picid(9961);
	set_level(130);
	set_max_hp(10000000);
	//     set_max_hp(10);
	set_max_mp(20000);
	init_fight_status();
	set_walk_speed(2);
	set_attack_speed(10);
	set_walk_step(2);
	set_max_seek(8);
	//        set("no_sk04237",1);	//玄龙决对其没有效果
	set("no_sk04211", 1);	//变身术对其没有效果
	set("anti_sleep", 1);	//不会昏迷
	set("anti_no_move", 1); //不会冻结

	set_skill(11001, 100);
	set_skill(11002, 100);

	setup();
	set_char_type(OFFICER_TYPE);
	set("birthday", time());
	if (!clonep(me))
		return;
	//	CHAT_D->rumor_channel( 0, CHAT+"Vạn Ác Chi Long đã xuất hiện tại Thiên Ngoại Ảo Cảnh tầng 5. Nghe nói con quái vật này mang sức mạnh của Kỳ Dị Thú, uy lực kinh người. Hãy thận trọng khi chiến đấu!" );
	set_2("talk", (["fight":(
								: do_fight:),
	]));
	log_file("boss.txt", short_time() + " Sơn Đại Vương xuất hiện\n");
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
void set_lowhp_status()
{
	add_ap(get_ap() / 5);
	add_dp(get_dp() / 5);
	add_cp(get_cp() / 5);
	add_pp(get_pp() / 5);
	add_sp(get_sp() / 5);
}
void heart_beat_walk()
{
	int i, x, y, z, x0, y0, z0, p, x1, y1;
	object enemy, me = this_object();

	if (get_char_type() == OFFICER_TYPE) //普通状态
	{
		if (gone_time(hptime) >= 10)
		{
			add_hp(100);
			hptime = time();
			if (lowhp && get_hp() * 100 / get_max_hp() > 40)
			{
				lowhp = 0;
				init_fight_status();
			}
		}
		return;
	}
	enemy = get_enemy();
	if (objectp(enemy))
	{
		if (gone_time(saytime) >= 60)
		{
			saytime = time();
			if (random(2))
			{
				switch (random(3))
				{
				case 0:
					SAY_CMD->say(me, "Loạn Huyết!");
					break;
				case 1:
					SAY_CMD->say(me, "Huyền Thiên Nộ Khí");
					break;
				default:
					SAY_CMD->say(me, enemy->get_name() + " hãy đỡ pháp thuật của bổn tọa! ");
					break;
				}
			}
		}
		if (enemy->is_die())
			set_enemy(0);
	}
	else if (RelaxTime == 0)
	{
		RelaxTime = time();
	}
	if (RelaxTime && gone_time(RelaxTime) >= 60)
	{
		RelaxTime = 0;
		set_char_type(OFFICER_TYPE);
		//		add_to_scene(174,190,160);
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
	if (gone_time(hptime) >= 10)
	{
		add_hp(100);
		hptime = time();
		if (lowhp && get_hp() * 100 / get_max_hp() > 40)
		{
			lowhp = 0;
			init_fight_status();
		}
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
		"skill/02/02415"->perform_action_npc(me, enemy);
		return;
	}
	if (objectp(enemy = get_enemy()) && gone_time(leiTime) > 40)
	{
		leiTime = time();
		//百万雷鸣
		if (!lowhp && random(100) < 40)
			return "skill/11/11010"->perform_action_npc(me, 0);
		if (lowhp && random(100) < 60)
			return "skill/11/11011"->perform_action_npc(me, 0);
	}
	::heart_beat_walk();
}
void heart_beat_attack()
{
	if (get_char_type() == OFFICER_TYPE) //普通状态
		return;
	::heart_beat_attack();
}

void summon_guard()
{
	int i, x, y, z, count, p;
	object npc, me = this_object();

	x = get_x(me);
	y = get_y(me);
	z = get_z(me);
	for (i = 0; i < 100; i++)
	{
		p = get_valid_xy(z, x + random(10) - 5, y + random(10) - 5, IS_CHAR_BLOCK);
		if (!p)
			continue;
		npc = new ("npc/boss/00011");

		if (!npc)
			break;
		npc->add_to_scene(z, p / 1000, p % 1000);
		npc->set_owner(me);
		NPC_SLAVE_D->find_enemy(npc); // 寻找敌人
		send_user(get_scene_object_2(npc, USER_TYPE), "%c%d%w%c%c%w%c%c%w%c%c%c", 0x6f, getoid(npc),
				  41311, 1, OVER_BODY, 41312, 1, OVER_BODY, 41313, 1, UNDER_FOOT, PF_ONCE);
		count++;
		if (count >= 2)
			break;
	}
	if (count == 0)
		return;
	count = 0;
	for (i = 0; i < 100; i++)
	{
		p = get_valid_xy(z, x + random(10) - 5, y + random(10) - 5, IS_CHAR_BLOCK);
		if (!p)
			continue;
		npc = new ("npc/boss/00012");
		if (!npc)
			break;
		npc->add_to_scene(z, p / 1000, p % 1000);
		npc->set_owner(me);
		npc->set_char_type(FIGHTER_TYPE);
		NPC_SLAVE_D->find_enemy(npc); // 寻找敌人
		send_user(get_scene_object_2(npc, USER_TYPE), "%c%d%w%c%c%w%c%c%w%c%c%c", 0x6f, getoid(npc),
				  41311, 1, OVER_BODY, 41312, 1, OVER_BODY, 41313, 1, UNDER_FOOT, PF_ONCE);
		count++;
		if (count >= 4)
			break;
	}
	summon = 1;
}
// 函数：特技攻击对手
int perform_action(object who)
{
	int rate, x, y, z, p, i, j, x1, y1, x0, y0, z0;
	object me = this_object();

	RelaxTime = 0;
	if (lowhp == 0 && get_hp() * 100 / get_max_hp() < 40) //生命值为40％以下
	{
		lowhp = 1;
		if (summon == 0)
			summon_guard();
		set_lowhp_status();
		SAY_CMD->say(me, "Loạn Huyết!");
	}

	if (gone_time(silent) >= 30)
	{
		z = get_z(who);
		z0 = get_z(me);
		if (z != z0)
			return 0;
		if ((i = distance_between(me, who)) > 2 && i < 20)
		{
			x = get_x(who);
			y = get_y(who);
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
				send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 32411, 1, OVER_BODY, PF_ONCE);

				me->add_to_scene(z, x1, y1);
				me->to_front_xy(x, y);
				//	                        send_user( me, "%c%w%w%w%c%c%c", 0x4f, x0, y0, 32411, 1, OVER_BODY, PF_ONCE );    // 补发指令

				silent = time();
				return PF_FILE_11002->perform_action_npc(me, who);
			}
		}
		else if (i < 2)
		{
			silent = time();
			return PF_FILE_11002->perform_action_npc(me, who);
		}
	}

	if (random100() < 10)
		return "skill/02/02415"->perform_action_npc(me, who);
	if (gone_time(leiTime) > 40)
	{
		leiTime = time();
		//百万雷鸣
		if (!lowhp && random(100) < 40)
			return "skill/11/11010"->perform_action_npc(me, 0);
		if (lowhp && random(100) < 60)
			return "skill/11/11011"->perform_action_npc(me, 0);
	}
	rate = random(100);
	if (lowhp == 0)
	{
		if (rate < 50)
			return PF_FILE_11001->perform_action_npc(me, who);
	}
	else
	{
		if (rate < 40)
			return PF_FILE_11003->perform_action_npc(me, who);
	}
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

	log_file("boss.txt", short_time() + " Sơn Đại Vương bị tiêu diệt\n");

	if (!objectp(who = me->get_enemy_4()))
		return;

	if (owner = who->get_owner())
		who = owner;
	if (who->is_npc())
		return;

	//	who->add_title("A001");
	//	who->show_title("A001");
	CHAT_D->rumor_channel(0, CHAT + "Nghe nói Âm Linh Đạo Trưởng đã bị " + who->get_name() + " đánh bại. Thật là dũng mãnh!");
	drop_items(me, who);
	"cmd/base/time"->set_amlinhdaotruong(0);
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
	exp = 50000;
	for (i = 0; i < size; i++)
		if (team[i])
		{
			level2 = level - team[i]->get_level();
			exp2 = exp * team[i]->get_level() / alllevel;
			exp2 = me->correct_exp_bonus(level, level2, exp2) * who->get_online_rate() / 100;

			if (exp2 < 5)
				exp2 = 5;
			team[i]->add_exp(exp2);
			team[i]->add_potential(10000);
			team[i]->add_log("#hill_king", 1);
			team[i]->add_log("&hill_king", exp2);
			team[i]->add_log("*hill_king", 100);
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
	//	if ( rate < rate1 )
	{
		for (i = 0; i < 5; i++) //10堆5000金
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
		// for (i = 0; i < 5; i++)
		// {
		// 	if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
		// 	{
		// 		item = new ("/item/sell/3032");
		// 		TEAM_D->drop_item(item, who);
		// 		item->set_user_id(owner);
		// 		item->add_to_scene(z, p / 1000, p % 1000);
		// 		item->set("winner", who);
		// 		item->set("time", time());
		// 	}
		// }
		// if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
		// {
		// 	item = new ("/item/sell/4032");
		// 	TEAM_D->drop_item(item, who);
		// 	item->set_user_id(owner);
		// 	item->add_to_scene(z, p / 1000, p % 1000);
		// 	item->set("winner", who);
		// 	item->set("time", time());
		// }
		for (i = 0; i < 5; i++)
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				switch (random(5))
				{
				case 0:
					item = new ("/item/sell/0032");
					break;
				case 1:
					item = new ("/item/sell/1032");
					break;
				case 2:
					item = new ("/item/sell/2032");
					break;
				}
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
		for (i = 0; i < 2; i++)
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{

				item = new ("/item/sell/2032");

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
		for (i = 0; i < random(2) + 2; i++)
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				item = new ("/item/TuiLinhThach/NgauNhien/2");
				if (!item)
					continue;
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
		for (i = 0; i < random(4) + 2; i++)
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				item = new ("/item/TuiLinhThach/NgauNhien/1");
				if (!item)
					continue;
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
		for (i = 0; i < random(2) + 2; i++)
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				item = new ("/item/TuiLinhThach/NgauNhien/3");
				if (!item)
					continue;
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
		for (i = 0; i < 2; i++)
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				item = new ("/item/TuiLinhThach/NgauNhien/4");
				if (!item)
					continue;
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}

		for (i = 0; i < 20; i++)
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)) //Tù Và Chiến Quốc
			{
				item = new ("/item/91/9167");
				if (!item)
					return;
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
		// for (i = 0; i < 2; i++)
		// {
		// 	if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
		// 	{
		// 		item = new ("/tran/an/an");
		// 		TEAM_D->drop_item(item, who);
		// 		item->set_user_id(owner);
		// 		item->add_to_scene(z, p / 1000, p % 1000);
		// 		item->set("winner", who);
		// 		item->set("time", time());
		// 	}
		// }
	}
	p = get_valid_xy(z, x, y, IS_ITEM_BLOCK);
	if (!p)
		return;
	rate = random(10000);
	if (rate < 3000 * rate1 / 100) //60级的随机门派金色装备
	{
		nTmp = WEAPON_FILE->get_family_equip(nFamily[random(7)], 0, 60, HEAD_TYPE + random(6));
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
	else if (rate < 3500 * rate1 / 100) //紫参丹
	{
		for (i = 0; i < 4; i++)
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
	else if (rate < 6000 * rate1 / 100) //60等级段随机蓝色配方
	{
		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
		{
			item = new ("/quest/product2"->get_random_level_blue_product(60, 60));
			TEAM_D->drop_item(item, who);
			item->set_user_id(owner);
			item->add_to_scene(z, p / 1000, p % 1000);
			item->set("winner", who);
			item->set("time", time());
		}
	}
	else if (rate < 6500 * rate1 / 100) //随机技能进阶
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

	else if (rate < 10000 * rate1 / 100) //Chiến Quốc Lệnh
	{
		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
		{
			item = new ("/item/08/0001");
			if (!item)
				return;
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
	send_user(who, "%c%c%w%s", ':', 3, 9961, "Âm Linh Đạo Trưởng:\n Hãy theo bổn tọa, ta sẽ giúp các người bước vào Ma Đạo tu luyện!\n" + sprintf(ESC "Khiêu chiến\ntalk %x# fight\n", getoid(this_object())) + ESC "Rời khỏi");
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