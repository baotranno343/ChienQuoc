#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <effect.h>
#include <cmd.h>
#include <skill.h>
#include <task.h>
#include <action.h>
#include <city.h>

inherit BADMAN;

int saytime, hptime, RelaxTime, pTime, pTime1, pTime2, pTime3, iRelax, i3484, i2415, i2513, i2516;
int tao_quai(int z, int level);
void create()
{
	set_name("x");
	set_level(120);
	set_hit_rate(200);
	set_hit_rate_3(60);
	set_walk_speed(3);
	set_attack_speed(1);
	set_max_seek(6);
	set_walk_step(2);

	set("no_sk04211", 1);	//变身术对其没有效果
	set("anti_sleep", 1);	//不会昏迷
	set("anti_no_move", 1); //不会冻结
	set("anti_blind", 1);	//No Blind
	setup();
	set_char_type(FIGHTER_TYPE_2);
}
void init(int level)
{
	object me = this_object();
	switch (level)
	{
	case 10:
		me->set_name("Thập Phá Thiên Đầu Lĩnh");
		me->set_char_picid(1264);
		break;
	case 20:
		me->set_name("Nhị Thập Phá Thiên Đầu Lĩnh");
		me->set_char_picid(1280);
		break;
	case 30:
		me->set_name("Tam Thập Phá Thiên Đầu Lĩnh");
		me->set_char_picid(1284);
		break;
	case 40:
		me->set_name("Tứ Thập Phá Thiên Đầu Lĩnh");
		me->set_char_picid(1286);
		break;
	case 50:
		me->set_name("Ngũ Thập Phá Thiên Đầu Lĩnh");
		me->set_char_picid(1238);
		break;

	default:
		me->set_name("Vô Danh Tiểu Tốt");
		me->set_char_picid(800);
		break;
	}

	me->set_max_hp(2000000 * level / 8);
	me->set_max_mp(500 * level / 10);
	me->set_double_rate(1000 * level / 10);
	me->set_ap(1200 * level / 10);
	me->set_cp(450 * level / 10);
	me->set_dp(1200 * level / 10);
	me->set_pp(1200 * level / 10);
	me->set_sp(500 * level / 10);
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

// 函数：列示给玩家看(新进入场景)(NPC 专用)

int perform_action(object who)
{
	int rate, x, y, z, i, size, ret, type, interval, cp;
	object me = this_object(), *char;

	if (!who)
		return 2;
	if (who->is_die())
		return 2;
	if (distance_between(me, who) > me->get_max_seek())
	{
		return 0;
	}
	RelaxTime = 0;
	iRelax = 0;

	if (gone_time(i3484) > 30)
	{
		i3484 = time();
		char = get_scene_object_2(me, USER_TYPE);
		set_effect(me, EFFECT_03484, 300);
		send_user(me, "%c%w%w%c", 0x81, 3484, get_effect_3(me, EFFECT_03484), EFFECT_GOOD);
		send_user(char - ({me}), "%c%d%w%c%c", 0x83, getoid(me), 3484, 1, EFFECT_GOOD);
		send_user(char, "%c%d%w%c%c%c", 0x6f, getoid(me), 32521, 1, OVER_BODY, PF_ONCE);
		me->set_save("3484_1", 500);
		me->set_save("3484_2", 1000);
	}
	if (gone_time(i2513) > 15)
	{
		i2513 = time();
		send_user(me, "%c%d%w%c%c%c", 0x6f, getoid(me), 10101, 1, OVER_BODY, PF_STOP); // 删除聚气
		send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 35139, 1, OVER_BODY, PF_ONCE);
		send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(who), 25131, 1, OVER_BODY, 25132, 1, OVER_BODY, PF_ONCE);
		ret = CHAR_FIGHT_D->attack_done(me, who, 10 + (me->get_skill(0251) - 1) / 10 * 8);
		ret += CHAR_FIGHT_D->attack_done(me, who, 10 + (me->get_skill(0251) - 1) / 10 * 8);
		if (who && !who->is_die())
			CHAR_FIGHT_D->set_enmity(me, who, 100);

		if (!who)
			return 2; // 执行成功
		if (who->is_anti_effect())
			return 2;
		if (get_effect(who, EFFECT_NO_WEAPON_0))
			return 2;
		if (who->get_2("suit_effect.no_drop"))
			return 2; //套装

		if (ret > 0) // rate - who->get_immunity()
		{
			send_user(who, "%c%w%w%c", 0x81, 9020, get_effect_3(who, EFFECT_CHAR_WOUND), EFFECT_BAD);
			set_effect(who, EFFECT_NO_WEAPON, 4);
			set_effect(who, EFFECT_NO_WEAPON_0, 6);
			send_user(who, "%c%w%w%c", 0x81, 2114, 4, EFFECT_BAD);
			if (who->is_user())
			{
				USER_ENERGY_D->count_all_prop(who);
				send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w", 0x7c, getoid(who), UNARMED);
			}
			else
			{
				who->set("02114", 1000);
				who->add_ap(-1000);
			}
		}
	}
	if (gone_time(i2516) > 2)
	{
		i2516 = time();
		send_user(me, "%c%d%w%c%c%c", 0x6f, getoid(me), 10101, 1, OVER_BODY, PF_STOP); // 删除聚气

		send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%w%c%c%c", 0x6f, getoid(who),
				  25163, 1, OVER_BODY, 25164, 1, OVER_BODY, PF_ONCE);
		me->set("add_damage", 150);
		ret = CHAR_FIGHT_D->attack_done(me, who, HIT_NONE);
		ret += CHAR_FIGHT_D->attack_done(me, who, HIT_NONE);
		if (who && !who->is_die())
			CHAR_FIGHT_D->set_enmity(me, who, 80);
		me->set("add_damage", 0);
		if (!who)
			return 2; // 执行成功

		if (ret > 0) // rate - who->get_immunity()
		{
			if (get_effect_3(who, EFFECT_NO_CLOTH_0))
				return 2;
			send_user(get_scene_object_2(who, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(who), 21142, 1, OVER_BODY, PF_ONCE); // 技能成功
			set_effect(who, EFFECT_NO_CLOTH, 5);
			set_effect(who, EFFECT_NO_CLOTH_0, 7);
			CHAR_CHAR_D->init_loop_perform(who);
			send_user(who, "%c%w%w%c", 0x81, 2516, 5, EFFECT_BAD);
			send_user(get_scene_object_2(who, USER_TYPE) - ({who}), "%c%d%w%c%c", 0x83, getoid(who), 2516, 1, EFFECT_BAD);
			if (who->is_user())
			{
				USER_ENERGY_D->count_all_prop(who);
			}
			else
			{
				who->set("02516", 1150);
				who->add_dp(-1150);
			}
		}
	}
	if (gone_time(pTime1) > 4)
	{
		pTime1 = time();
		char = get_scene_object_2(me, USER_TYPE) - ({me});
		if (!sizeof(char))
			return;
		who = char[random(sizeof(char))];
		switch (random(3))
		{
		default:
			"skill/02/02410"->perform_action_npc(me, who);
			break;
		case 1:
			"skill/02/02512"->perform_action_npc(me, who);
			break;
		case 2:
			"skill/02/02413"->perform_action_npc(me, who);
			break;
		}
		return 1;
	}
	if (gone_time(pTime2) > 3)
	{
		pTime2 = time();
		me->add_hp(2000 * (100 + me->get_healing_rate()) / 100);
		send_user(get_scene_object_2(me, USER_TYPE), "%c%d%w%c%c%c", 0x6f, getoid(me), 9154, 1, OVER_BODY, PF_ONCE);
		return 1;
	}
	send_user(get_scene_object_2(me, USER_TYPE), "%c%d%d%c%c%c%d", 0x41, getoid(me), time2(), 1, 10, get_d(me), getoid(who));
	ret = CHAR_FIGHT_D->attack_done(me, who, HIT_NONE, 10 + (me->get_skill(0423) - 1) / 10 * 8);
	ret += CHAR_FIGHT_D->attack_done(me, who, HIT_NONE, 10 + (me->get_skill(0423) - 1) / 10 * 8);
	//if (who->get("anti_faint"))
	//return 2;
	if (ret > 0 && random(100) < 30)
	{
		if (!who)
			return 1;
		if (get_effect(who, EFFECT_CHAR_FAINT) || get_effect(who, EFFECT_CHAR_FAINT_0))
			return 1; // 执行成功
		if (who->get_perform("02222#"))
			return 1;
		char = get_scene_object_2(who, USER_TYPE);
		set_effect(who, EFFECT_CHAR_FAINT, 3); // 小心准备 me
		CHAR_CHAR_D->init_loop_perform(who);
		if (get_heart_state(who) == MAGIC_STAT)
			send_user(char, "%c%d%d%c", 0x40, getoid(who), time2(), MAGIC_ACT_END); // 结束施法动作
		send_user(who, "%c%w%w%c", 0x81, 9002, get_effect_3(who, EFFECT_CHAR_FAINT), EFFECT_BAD);
		send_user(char - ({who}), "%c%d%w%c%c", 0x83, getoid(who), 9002, 1, EFFECT_BAD);
		send_user(char, "%c%d%w%c%c%c", 0x6f, getoid(who), 9002, 10, OVER_BODY, PF_LOOP);
	}
	return 1;
}

void drop_items(object who) { __FILE__->drop_items_callout(this_object(), who); }

void drop_items_callout(object me, object who)
{
	object item, leader, map, *member, npc1;
	string file, owner, id;
	int p, rate, i, size, gold, equip, rate1, tId, level;
	int z, x, y, s;
	map = get_map_object(get_z(me));
	if (!map)
		return;
	map->add("die", 1);
	z = map->get_id();
	if (map->get("die") == map->get("amount"))
	{
		npc1 = new ("ken/pb/pbbox");
		npc1->add_to_scene(z, 34, 30);
	}
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
	s = map->get("S") / 10;
	if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)) //随机宠物技能书
	{
		switch (s)
		{
		case 1:
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)) //随机宠物技能书
			{
				item = new ("item/kham/tuibaothach1");
				if (item)
				{
					TEAM_D->drop_item(item, who);
					item->set_user_id(owner);
					item->add_to_scene(z, p / 1000, p % 1000);
					item->set("winner", who);
					item->set("time", time());
				}
			}
			break;
		case 2:
			for (i = 0; i < 3; i++)
			{
				if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)) //随机宠物技能书
				{
					item = new ("item/kham/tuibaothach1");
					if (item)
					{
						TEAM_D->drop_item(item, who);
						item->set_user_id(owner);
						item->add_to_scene(z, p / 1000, p % 1000);
						item->set("winner", who);
						item->set("time", time());
					}
				}
			}

			break;
		case 3:

			for (i = 0; i < 5; i++)
			{
				if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)) //随机宠物技能书
				{
					item = new ("item/kham/tuibaothach1");
					if (item)
					{
						TEAM_D->drop_item(item, who);
						item->set_user_id(owner);
						item->add_to_scene(z, p / 1000, p % 1000);
						item->set("winner", who);
						item->set("time", time());
					}
				}
			}

			if (random(100) < 20)
			{
				if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)) //随机宠物技能书
				{
					item = new ("item/kham/tuibaothach2");
					if (item)
					{
						TEAM_D->drop_item(item, who);
						item->set_user_id(owner);
						item->add_to_scene(z, p / 1000, p % 1000);
						item->set("winner", who);
						item->set("time", time());
					}
				}
			}
			break;
		case 4:
			for (i = 0; i < 3; i++)
			{
				if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)) //随机宠物技能书
				{
					item = new ("item/kham/tuibaothach2");
					if (item)
					{
						TEAM_D->drop_item(item, who);
						item->set_user_id(owner);
						item->add_to_scene(z, p / 1000, p % 1000);
						item->set("winner", who);
						item->set("time", time());
					}
				}
			}

			break;
		case 5:
			for (i = 0; i < 2; i++)
			{
				if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)) //随机宠物技能书
				{
					item = new ("item/kham/tuibaothach3");
					if (item)
					{
						TEAM_D->drop_item(item, who);
						item->set_user_id(owner);
						item->add_to_scene(z, p / 1000, p % 1000);
						item->set("winner", who);
						item->set("time", time());
					}
				}
			}

			break;
		default:
			break;
		}
	}
	for (i = 0; i < random(3); i++)
	{
		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)) //随机宠物技能书
		{
			item = new ("/item/test2/TuiPhapBao");
			if (!item)
				continue;
			TEAM_D->drop_item(item, who);
			item->set_user_id(owner);
			item->add_to_scene(z, p / 1000, p % 1000);
			item->set("winner", who);
			item->set("time", time());
		}

		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)) //随机宠物技能书
		{
			item = new ("/item/test2/TuiQuaVoSong");
			if (!item)
				continue;
			TEAM_D->drop_item(item, who);
			item->set_user_id(owner);
			item->add_to_scene(z, p / 1000, p % 1000);
			item->set("winner", who);
			item->set("time", time());
		}
	}

	if (random(100) < 2 * s)
	{
		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)) //随机宠物技能书
		{
			item = new ("item/kham/tuibaothach3");
			if (item)
			{
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
	}
}