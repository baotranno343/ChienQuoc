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
int saytime, hptime, RelaxTime, pTime, pTime1, iRelax;
string *nFamily = ({"Đào Hoa Nguyên", "Thục Sơn", "Cấm Vệ Quân", "Đường Môn", "Mao Sơn", "Côn Luân", "Vân Mộng Cốc"});
// 函数：是否不能进城
int cannot_enter_city() { return 1; }
int get_id_color() { return 0x800080; }
//int is_caster () { return 1; }
void drop_items(object me, object who);

// 函数：获取人物名称
//string get_short()
//{
//        return this_object()->get_name();
//}
int set_fight_status(int level)
{
	int i;
	object me = this_object();

	if (level < 40)
		level = 40;
	level += random(5);
	set_level(level);
	i = level / 5;
	set_max_hp(15000 + 5000 * i);
	set_max_mp(0);
	set_ap(600 + 155 * i);
	set_dp(450 + 140 * i);
	set_cp(200 + 110 * i);
	set_pp(300 + 130 * i);
	set_sp(180 + 130 * i);
	set_skill(0261, 23);
	set_skill(0221, 4);
	set_skill(0211, 34);
}
// 函数：构造处理
void create()
{
	object me = this_object();
	set_name("Hổ Cảnh Kính Ma");
	set_head_color(0x4a8f);
	set_char_picid(0701);
	set_fight_status(45);
	set_walk_speed(3);
	set_attack_speed(15);
	set_max_seek(6);
	set_walk_step(2);
	set("no_sk04211", 1);	//变身术对其没有效果
	set("anti_sleep", 1);	//不会昏迷
	set("anti_no_move", 1); //不会冻结

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
	int rate;
	object me = this_object();

	if (distance_between(me, who) > me->get_max_seek())
	{
		return 0;
	}
	rate = random100();
	if (rate < 5)
	{
		return "skill/02/02614"->perform_action_npc(me, who);
	}
	else if (rate < 15)
	{
		return "skill/02/02211"->perform_action_npc(me, who);
	}
	else if (rate < 20)
	{
		return "skill/02/02114"->perform_action_npc(me, who);
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
	object owner, *team, map;
	int level, level2, exp, exp2, pot, alllevel;
	int i, size, status, time, flag;

	map = me->get("map");
	if (map)
		map->add("beat_boss", 1);
	if (!objectp(who = me->get_enemy_4()))
		return;

	if (owner = who->get_owner())
		who = owner;
	if (who->is_npc())
		return;

	drop_items(me, who);
}

// 函数：掉宝奖励
void drop_items(object me, object who)
{
	int x, y, z, p, i, rate, rate1, rate2, level;
	string *nTmp, id, owner;
	object item, leader;

	z = get_z(me);
	x = get_x(me);
	y = get_y(me);
	id = who->get_leader();
	level = me->get_level();
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
		//金钱
		for (i = 0; i < 10; i++)
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				item = new ("/item/std/0001");
				item->set_value(300);
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
		//随机门派蓝色装备1件
		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
		{
			nTmp = WEAPON_FILE->get_family_equip(nFamily[random(7)], 0, level, HEAD_TYPE + random(6));
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
		//活络丸
		for (i = 0; i < 4; i++)
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				item = new ("item/91/9101");
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
		for (i = 0; i < 10; i++)
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				item = new ("item/test/pyktanthu");
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
		switch (random(2))
		{
		case 0:
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				item = new ("quest/product2"->get_random_level_yellow_product(117, 117));
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
			break;

		default:
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				item = new ("quest/product2"->get_random_level_yellow_neck_product(116, 116));
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
			break;
		}
		/*	//Âu Dã Bảo Thạch
		if( "sys/sys/count"->get_new_story() && (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)) )
                {
                        //item = new( "item/08/0014" );
						item = new( "item/08/0016" );
                        TEAM_D->drop_item(item,who);
			item->set_user_id(owner);
                        item->add_to_scene(z, p / 1000, p % 1000);
                        item->set("winner", who);
                        item->set( "time", time() );
                }	*/
		if ("sys/sys/count"->get_new_story() && (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)))
		{
			item = new ("/item/08/0016");
			item->set_amount(2);
			if (!item)
				return;
			TEAM_D->drop_item(item, who);
			item->set_user_id(owner);
			item->add_to_scene(z, p / 1000, p % 1000);
			item->set("winner", who);
			item->set("time", time());
		}
		if ("sys/sys/count"->get_new_story() && (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)))
		{
			item = new ("/item/08/0017");
			item->set_amount(2);
			if (!item)
				return;
			TEAM_D->drop_item(item, who);
			item->set_user_id(owner);
			item->add_to_scene(z, p / 1000, p % 1000);
			item->set("winner", who);
			item->set("time", time());
		}
		if ("sys/sys/count"->get_new_story() && (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK)))
		{
			item = new ("/item/test/vosongdiemphieu");
			item->set_amount(5);
			if (!item)
				return;
			TEAM_D->drop_item(item, who);
			item->set_user_id(owner);
			item->add_to_scene(z, p / 1000, p % 1000);
			item->set("winner", who);
			item->set("time", time());
		}
		rate2 = random(1000);
		if (rate2 < 599)
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				item = new ("item/std/8000"); //藏宝图
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
		else if (rate2 < 600)
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				item = new ("item/std/8005"); //残旧藏宝图
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
		else //随机白色生活技能图纸
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				item = new ("quest/product2"->get_random_level_white_product(60, 110));
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
	}
	if (random(100) < 70 * rate1 / 100)
	{
		rate2 = random(100);
		if (rate2 < 75)
		{
			//随机门派蓝色装备1件
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				nTmp = WEAPON_FILE->get_family_equip(nFamily[random(7)], 0, level, HEAD_TYPE + random(6));
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
		}
		else //气脉丹、周天丹、逍遥散、金桑散、紫心丹、归元丹随机一个
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				switch (random(6))
				{
				case 0:
					item = new ("/item/91/9160");
					break;
				case 1:
					item = new ("/item/91/9161");
					break;
				case 2:
					item = new ("/item/91/9162");
					break;
				case 3:
					item = new ("/item/91/9163");
					break;
				case 4:
					item = new ("/item/91/9164");
					break;
				case 5:
					item = new ("/item/91/9165");
					break;
				}
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
	}
	if (random(100) < 20 * rate1 / 100)
	{
		rate2 = random(100);
		if (rate2 < 90) //随机门派进阶书
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
		else //随机收藏品
		{
			if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
			{
				item = new (COLLECT_FILE->get_collect_file());
				TEAM_D->drop_item(item, who);
				item->set_user_id(owner);
				item->add_to_scene(z, p / 1000, p % 1000);
				item->set("winner", who);
				item->set("time", time());
			}
		}
	}
	if (random(100) < 2 * rate1 / 100)
	{
		//随机门派金色装备1件
		if (p = get_valid_xy(z, x, y, IS_ITEM_BLOCK))
		{
			nTmp = WEAPON_FILE->get_family_equip(nFamily[random(7)], 0, level, HEAD_TYPE + random(6));
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
	}
	/*	if ( "sys/sys/count"->get_new_story() && (random(1000) < 5 * rate1*10/1000) )
	{
		//Can Tương Bảo Thạch
                if( p = get_valid_xy(z, x, y, IS_ITEM_BLOCK) )
                {
                        //item = new( "item/08/0015" );
						item = new( "item/08/0017" );
                        TEAM_D->drop_item(item,who);
			item->set_user_id(owner);
                        item->add_to_scene(z, p / 1000, p % 1000);
                        item->set("winner", who);
                        item->set( "time", time() );
                }
	}*/
}