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
int saytime, hptime, RelaxTime, pTime, pTime1, iRelax, pTime3;
string *nFamily = ({"Đào Hoa Nguyên", "Thục Sơn", "Cấm Vệ Quân", "Đường Môn", "Mao Sơn", "Côn Luân", "Vân Mộng Cốc"});
// 函数：是否不能进城
int cannot_enter_city() { return 1; }
int get_id_color() { return 0x800080; }
int is_caster() { return 1; }
void drop_items(object me, object who);
int skill_04236(object me, object who);

// 函数：修正经验奖励
int correct_exp_bonus(int level, int level2, int exp) { return exp; }

// 函数：修正掉宝率
int correct_drop_rate(int level) { return 100; }

// 函数：获取人物名称
string get_short()
{
	return this_object()->get_name();
}

void init_fight_status()
{
	set_ap(2500);
	set_dp(2000);
	set_cp(2500);
	set_pp(2000);
	set_sp(600);
}

// 函数：构造处理
void create()
{
	object me = this_object();
	set_name("Liêm Pha");
	set_char_picid(5201);
	set_level(90);
	set_max_hp(1500000);
	set_max_mp(1000);
	init_fight_status();
	set_walk_speed(3);
	set_attack_speed(20);
	set_max_seek(6);
	set_walk_step(2);
	set("no_sk04211", 1);	//变身术对其没有效果
	set("anti_sleep", 1);	//不会昏迷
	set("anti_no_move", 1); //不会冻结

	set_skill(0414, 45);

	setup();
	set_char_type(FIGHTER_TYPE_2);
	set("birthday", time());
	set_enmity_flag(1);
}

int can_fight(object who)
{
	object owner;
	string leader, id;
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
	if (who->is_npc() && objectp(owner = who->get_owner()))
		who = owner;
	if (who->is_npc())
	{
		set_enemy(0);
		return 0;
	}

	return ::can_be_fighted(who);
}

void heart_beat_walk()
{
	int i, x, y, z, x0, y0, z0, p, x1, y1;
	object enemy, me = this_object();

	if (iRelax)
		return;
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
				SAY_CMD->say(me, "Loạn Huyết!");
			}
		}
	}
	else if (RelaxTime == 0)
	{
		RelaxTime = time();
	}
	if (RelaxTime && gone_time(RelaxTime) >= 120)
	{
		RelaxTime = 0;
		init_fight_status();
		iRelax = 1;
		me->add_to_scene(get_z(me), 123, 89, 4);
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

	::heart_beat_walk();
}
void heart_beat_attack()
{
	::heart_beat_attack();
}

// 函数：特技攻击对手
int perform_action(object who)
{
	int rate, x, y, z, i, size;
	object me = this_object(), *char;

	if (distance_between(me, who) > me->get_max_seek())
	{
		return 0;
	}
	RelaxTime = 0;
	iRelax = 0;
	if (gone_time(pTime) > 30)
	{
		pTime = time();
		SAY_CMD->say(me, "Liệt Hỏa Chú!");
		char = get_range_object(get_z(me), get_x(me), get_y(me), 10, USER_TYPE) + get_range_object(get_z(me), get_x(me), get_y(me), 10, CHAR_TYPE) - ({me, 0});
		for (i = 0, size = sizeof(char); i < size; i++)
			"skill/04/04231"->perform_action_npc(me, char[i]);
		return 1;
	}
	if (gone_time(pTime1) > 20)
	{
		pTime1 = time();
		char = get_scene_object_2(me, USER_TYPE) + get_scene_object_2(me, CHAR_TYPE) - ({me, 0});
		if (!sizeof(char))
			return;
		who = char[random(sizeof(char))];
		switch (random(4))
		{
		default:
			"skill/04/04143"->perform_action_npc(me, who);
			break;
		case 1:
			"skill/04/04144"->perform_action_npc(me, who);
			break;
		case 2:
			"skill/04/04145"->perform_action_npc(me, who);
			break;
		case 3:
			"skill/04/04148"->perform_action_npc(me, who);
			break;
		}
		return 1;
	}
	if (gone_time(pTime3) > 25)
	{
		pTime3 = time();
		SAY_CMD->say(me, "Hàn Băng Pháp Trận!");
		return skill_04236(me, who);
	}
	return PF_FILE_04232->perform_action_npc(me, who);
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
	int i, size, status, time, flag, kk;
	int z, x, y, p;
	object npc;
	z = get_z(me);
	x = get_x(me);
	y = get_y(me);
	if (p = get_valid_xy(z, x, y, IS_CHAR_BLOCK))
	{
		npc = new ("/npc/copy/NPC1");
		npc->set("tang", 6);
		npc->add_to_scene(z, p / 1000, p % 1000);
	}
	if (!objectp(who = me->get_enemy_4()))
		return;

	if (owner = who->get_owner())
		who = owner;
	if (who->is_npc())
		return;

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
	exp = 1400000;
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
			if (team[i]->get_legend(TASK_2_00, 4) && !team[i]->get_legend(TASK_2_00, 5) && team[i]->get_save("fb_002_001") < 1)
			{
				if ((kk = team[i]->add_save("fb_002_001", 1)) >= 1)
				{
					send_user(team[i], "%c%c%c%w%w%s", 0x51, 2, 2, TID_ZHOUGUO, 102, "邪恶的厨师(完成)");
					team[i]->set_legend(TASK_2_00, 5);
				}
				USER_TASK_D->send_task_intro(team[i], 2, TID_ZHOUGUO, 102);
				send_user(team[i], "%c%s", '!', sprintf(HIY "Lương Hưng %d/1", kk));
			}
			team[i]->add_log("#copyboss1", 1);
			team[i]->add_log("&copyboss1", exp2);
			team[i]->add_log("*copyboss1", 100);
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

	if (random(100) < rate1) //必掉(有等级修正)
	{

		for (i = 0; i < random(6); i++)
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				item = new ("/item/std/0001");
				item->set_value(10000);
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}

		for (i = 0; i < random(3); i++)
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
}

//寒冰法阵
int skill_04236(object me, object who)
{
	object *user;
	int z, i, size, x, y, cp;
	object *char;

	user = get_scene_object_2(me, USER_TYPE);

	z = get_z(me), x = get_x(me), y = get_y(me);
	send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(me),
			  4236, 1, UNDER_FOOT, 4236, 1, UNDER_FOOT, PF_ONCE);
	char = get_range_object(z, x, y, 3, USER_TYPE) + get_range_object(z, x, y, 3, CHAR_TYPE) - ({me});
	cp = me->get_cp();
	me->set_cp(150);
	for (i = 0, size = sizeof(char); i < size; i++)
		if (who = char[i])
		{
			if (who->get("anti_no_move")) //抗冻结
			{
				continue;
			}
			if (!who->can_be_fighted(me) || !me->can_fight(who))
				continue; // 执行成功
			if (get_effect(who, EFFECT_CHAR_NO_MOVE))
				continue; // 执行成功
			if (who->is_anti_effect())
				continue;
			send_user(who, "%c%c%c", 0x3d, 241, 1);	 // 更改走路步数
			set_effect(who, EFFECT_CHAR_NO_MOVE, 6); // 小心准备 me
			CHAR_CHAR_D->init_loop_perform(who);
			send_user(who, "%c%w%w%c", 0x81, 9002, get_effect_3(who, EFFECT_CHAR_NO_MOVE), EFFECT_BAD);
			send_user(get_scene_object_2(who, USER_TYPE) - ({who}), "%c%d%w%c%c", 0x83, getoid(who), 9002, 1, EFFECT_BAD);
			CHAR_FIGHT_D->cast_done(me, who);
			if (who)
				send_user(user, "%c%d%w%c%c%c", 0x6f, getoid(who), 9012, 1, OVER_BODY, PF_LOOP);
			if (who)
				CHAR_CHAR_D->init_loop_perform(who);
		}
	me->set_cp(cp);
	return 1;
}

//杀死一个敌人加2000气血
void stop_fight()
{
	object enemy;
	enemy = get_enemy();
	if (enemy && enemy->get_hp() == 0)
	{
		SAY_CMD->say(this_object(), "Ngưng Huyết Ly Hồn!");
		add_hp(2000);
	}
	::stop_fight();
}