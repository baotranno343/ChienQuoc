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
	me->set_name(sprintf("Phá Thiên Yêu Tầng %d", level));
	me->set_char_picid(800);

	me->set_max_hp(30000 + (level * 3000));
	me->set_max_mp(500 + (level * 20));
	me->set_double_rate(500 * level);
	me->set_ap(800 + (level * 20));
	me->set_cp(350 + (level * 20));
	me->set_dp(350 + (level * 5));
	me->set_pp(350 + (level * 5));
	me->set_sp(250 + (level * 5));
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

int perform_action(object who) { return 0; }

void drop_items(object who) { __FILE__->drop_items_callout(this_object(), who); }

void drop_items_callout(object me, object who)
{
	object item, leader, map, *member, npc1;
	string file, owner, id;
	int p, rate, i, size, gold, equip, rate1, tId, level;
	int z, x, y;
	map = get_map_object(get_z(me));
	if (!map)
		return;
	map->add("die", 1);
	z = map->get_id();
	x = get_x(me);
	y = get_y(me);
	if (map->get("die") == map->get("amount"))
	{
		npc1 = new ("ken/pb/pbbox");
		npc1->add_to_scene(z, 34, 30);
	}
	if (random(1000) < 5)
	{
		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)) //随机宠物技能书
		{
			item = new ("item/test2/tuibikipnm");
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

	else if (random(100) < 2)
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