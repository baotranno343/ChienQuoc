#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <effect.h>
#include <cmd.h>
#include <skill.h>
#include <task.h>
#include <action.h>

inherit NPC;

int flag;
int saytime, hptime, hptime2, silent, silent2, silent3, summon, RelaxTime, number = 1;
object *huohai = ({});
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
	set_ap(1600);
	set_dp(500);
	set_cp(900);
	set_pp(400);
	set_sp(1800);
}

// 函数：构造处理
void create()
{

	object me = this_object();
	set_name("Âm Gian Bại Đồ");
	set_char_picid(1255);
	set_level(85);
	set_max_hp(4500000);
	set_max_mp(2000);
	init_fight_status();
	set_walk_speed(4);
	set_attack_speed(25);
	set_walk_step(2);
	set_max_seek(8);
	set("no_sk04211", 1);	//变身术对其没有效果
	set("anti_sleep", 1);	//不会昏迷
	set("anti_no_move", 1); //不会冻结
	set("anti_05311", 1);	//不会迷魂
	set_skill(11012, 85);
	set_skill(11014, 85);

	set_head_color(0x2344);

	setup();
	set_char_type(OFFICER_TYPE);
	set("birthday", time());
	if (!clonep(me))
		return;
	CHAT_D->rumor_channel(0, CHAT + "Nghe nói Âm Gian Bại Đồ lại xuất hiện ở tầng sâu nhất của Địa Đạo Vạn Nhân.");
	set_2("talk", (["fight":(
								: do_fight:),
	]));
	set("guard", ({}));
	log_file("boss.txt", short_time() + "Âm Gian Bạn Đồ xuất hiện\n");
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
		if (gone_time(hptime) >= 10)
		{
			add_hp(100);
			hptime = time();
		}
		return;
	}
	enemy = get_enemy();
	if (objectp(enemy))
	{
		if (gone_time(saytime) >= 60)
		{
			saytime = time();
			if (random(10) > 1)
			{
				switch (random(3))
				{
				case 0:
					SAY_CMD->say(me, "Chém....chém....chém....gió");
					break;
				case 1:
					SAY_CMD->say(me, enemy->get_name() + ", hãy xem ta chém gió thành bão đây.");
					break;
				default:
					SAY_CMD->say(me, "Chém...chém....chém....gió.");
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
		for (i = 0; i < sizeof(huohai); i++)
		{
			if (!objectp(huohai[i]))
				continue;
			huohai[i]->remove_from_scene();
			destruct(huohai[i]);
		}
		huohai = ({});
		//		number=1;
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

	if (gone_time(hptime2) >= 2)
	{
		hptime2 = time();
		for (i = 0; i < sizeof(huohai); i++)
		{
			if (!objectp(huohai[i]))
				continue;
			add_hp(huohai[i]->get_hp_attract());
		}
	}

	::heart_beat_walk();
}
void heart_beat_attack()
{
	if (get_char_type() == OFFICER_TYPE) //普通状态
		return;
	::heart_beat_attack();
}
//召唤
void summon_guard()
{
	int i, x, y, z, count, p;
	object npc, me = this_object();

	x = get_x(me);
	y = get_y(me);
	z = get_z(me);
	//	for(i=0;i<number*4;i++)	//4个游魂祸害
	for (i = 0; i < 4; i++) //4个游魂祸害
	{
		//		if ( objectp(get(sprintf("guard%d",i))) )
		//			continue;
		p = get_valid_xy(z, x + random(10) - 5, y + random(10) - 5, IS_CHAR_BLOCK);
		if (!p)
			continue;
		npc = new ("npc/boss/00161");
		huohai += ({npc});
		if (!npc)
			break;
		//		set(sprintf("guard%d",i),npc);
		//		add("guard",({npc}));

		npc->add_to_scene(z, p / 1000, p % 1000);
		npc->set_owner(me);
		NPC_SLAVE_D->find_enemy(npc); // 寻找敌人
		send_user(get_scene_object_2(npc, USER_TYPE), "%c%d%w%c%c%w%c%c%w%c%c%c", 0x6f, getoid(npc),
				  41311, 1, OVER_BODY, 41312, 1, OVER_BODY, 41313, 1, UNDER_FOOT, PF_ONCE);
	}
}
// 函数：特技攻击对手
int perform_action(object who)
{
	int rate, x, y, z, p, i, j, x1, y1, x0, y0, z0, z2, x2, y2, size, damage, tt;
	object me = this_object();
	object user, owner, *char;

	RelaxTime = 0;

	if (gone_time(summon) >= 80) //召唤
	{
		for (i = 0, size = sizeof(huohai); i < size; i++)
		{
			if (!objectp(huohai[i]))
				continue;
			tt++;
		}
		if (tt + 4 <= 20)
		{
			summon = time();
			summon_guard();
		}
		//		if (number<5) number++;
	}
	if (gone_time(silent) >= 20)
	{
		silent = time();
		SAY_CMD->say(me, who->get_name() + ", Yaaaaaaaaaa.");
		return "skill/11/11012"->perform_action_npc(me, who); //冰霜咒
	}
	if (gone_time(silent2) >= 30)
	{
		silent2 = time();
		SAY_CMD->say(me, who->get_name() + ", Hãy đỡ đòn này của ta, đỡ nổi không ?");
		return "skill/11/11014"->perform_action_npc(me, who); //阴间之爪
	}

	if (gone_time(silent3) >= 300) // 死亡炸弹
	{
		silent3 = time();
		if (random100() < 50)
		{
			SAY_CMD->say(me, "Ta là vô đối!!!");
			for (i = 0, size = sizeof(huohai); i < size; i++)
			{
				if (!objectp(huohai[i]))
					continue;
				if (!who)
					return 0;
				z = get_z(who), x = get_x(who), y = get_y(who);
				damage = 200 + random(201);
				char = get_range_object(z, x, y, 2, USER_TYPE) + get_range_object(z, x, y, 2, CHAR_TYPE) - ({huohai[i]});
				for (j = 0; j < sizeof(char); j++)
					if (who = char[j])
					{
						if (who->is_npc())
							continue;
						send_user(get_scene_object_2(huohai[i], USER_TYPE), "%c%w%w%w%c%c%c", 0x4f, get_x(huohai[i]), get_y(huohai[i]), 9902, 1, OVER_BODY, PF_ONCE);
						send_user(who, "%c%d%w%c%d%w%c", 0x48, getoid(who), damage, get_d(who), 0, HIT_BLADE, 1);
						CHAR_DIE_D->is_enemy_die(huohai[i], who, damage);
					}
				huohai[i]->remove_from_scene();
				destruct(huohai[i]);
			}
			huohai = ({});
			//			number=1;
		}
	}
	if (!who)
		return 0;

	return "skill/11/11013"->perform_action_npc(me, who);

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

	CHAT_D->rumor_channel(0, CHAT + sprintf("Nghe nói Âm Gian Bại Đồ đã bị %s tiêu diệt rồi", who->get_name()));
	log_file("boss.txt", short_time() + "Âm Gian Bạn Đồ bị tiêu diệt\n");

	if (!objectp(who = me->get_enemy_4()))
		return;

	if (owner = who->get_owner())
		who = owner;
	if (who->is_npc())
		return;

	if (who->get_gender() == 1)
	{
		who->add_title("A007");
		who->show_title("A007");
	}
	else
	{
		who->add_title("A008");
		who->show_title("A008");
	}
	if (who->get_save_2("cantuong.status") == 1)
	{
		who->set_save_2("cantuong.agbd", 1);
		if (who->get_save_2("cantuong.count") >= 10000 &&
			who->get_save_2("cantuong.hv") >= 1 &&
			who->get_save_2("cantuong.agbd") >= 1 &&
			who->get_save_2("cantuong.uvdtq") >= 1 &&
			who->get_save_2("cantuong.ktl") >= 1)
			send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_CANTUONG, 1, "Tìm kiếm Thần Binh Phổ(Hoàn thành)");
		send_user(who, "%c%s", ';', "Đã tiêu diệt Âm Gian Bạn Đồ cần cho nhiệm vụ nâng cấp Tuyệt thế thần binh !");
	}
	//	who->add_title("Y200");
	//	who->show_title("Y200");
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
	exp = 50000;
	for (i = 0; i < size; i++)
		if (team[i])
		{
			level2 = level - team[i]->get_level();
			exp2 = exp * team[i]->get_level() / alllevel;
			exp2 = me->correct_exp_bonus(level, level2, exp2) * team[i]->get_online_rate() / 100;

			if (exp2 < 5)
				exp2 = 5;
			team[i]->add_exp(exp2);
			team[i]->add_potential(100);
			team[i]->add_log("#yinjian", 1);
			team[i]->add_log("&yinjian", exp2);
			team[i]->add_log("*yinjian", 100);
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
		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)) //70级或80级（二选一）的随机门派金色装备1件
		{
			nTmp = WEAPON_FILE->get_family_equip(nFamily[random(7)], 0, random(2) ? 70 : 80, HEAD_TYPE + random(6));
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
		for (i = 0; i < 5; i++) //10堆5000金
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
				item->set_level(2);
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
	p = get_valid_xy(z, x, y, IS_ITEM_BLOCK);
	if (!p)
		return;
	rate = random(10000);
	if (rate < 500 * rate1 / 100) //80级的随机门派金色装备
	{
		nTmp = WEAPON_FILE->get_family_equip(nFamily[random(7)], 0, 80, HEAD_TYPE + random(6));
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
	else if (rate < 2500 * rate1 / 100) //80级随机蓝色配方1个
	{
		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
		{
			item = new ("/quest/product2"->get_random_level_product(80, 80));
			TEAM_D->drop_item(item, who);
			item->set_user_id(owner);
			item->add_to_scene(z, p / 1000, p % 1000);
			item->set("winner", who);
			item->set("time", time());
		}
	}
	else if (rate < 5500 * rate1 / 100) //随机技能进阶三本
	{
		for (i = 0; i < 3; i++)
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
	}
	else if (rate < 7000 * rate1 / 100) //宝石矿 2个
	{
		for (i = 0; i < 2; i++)
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				item = new ("item/89/8992");
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
	}

	else if (rate < 9000 * rate1 / 100) //精致宝石矿 2个
	{
		for (i = 0; i < 2; i++)
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				item = new ("item/89/8993");
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
	}
	else if (rate < 10000 * rate1 / 100) //随机4级晶石3个
	{
		for (i = 0; i < 3; i++)
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
	}
	"/sys/npc/npc"->drop_ball(me, who);
}

void do_look(object who)
{
	send_user(who, "%c%c%w%s", ':', 3, 1255, "Âm Gian Bại Đồ:\n    Các ngươi muốn chém....chém....gió...thành....bão...à ?\n" + sprintf(ESC "Khiêu chiến\ntalk %x# fight\n", getoid(this_object())) + ESC "Rời khỏi");
}

void do_fight()
{
	object who = this_player(), me = this_object();

	if (get_char_type() != OFFICER_TYPE) //普通状态
		return;
	set_char_type(FIGHTER_TYPE_2);
	add_to_scene(get_z(me), get_x(me), get_y(me));
}
