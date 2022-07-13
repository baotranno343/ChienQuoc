/*-----------------------------------------------------------------------------------------*\
	《真假虎王》活动配置NPC ---- 真假虎王
	由cjxx创建
	使用此文件时需要配合活动主控文件。
\*-----------------------------------------------------------------------------------------*/
#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <effect.h>
#include <cmd.h>
#include <skill.h>
#include <action.h>

inherit NPC;

#define _DEBUG(str) ;								  //if(objectp(find_char("1"))) {tell_user(find_char("1"),str);}
#define ACTIVE_ANGEL_NPC "npc/party/gtt_active_angel" //	活动天使存放位置
#define GUESS_TRUE_TIGER "/sys/party/guess_true_tiger"

private
static function when_enemy_dead = 0;
private
static function when_enemy_be_hit = 0;
private
static int canfight = 0;

//	获取对手死亡时所执行的函数
function get_when_enemy_dead()
{
	return when_enemy_dead;
}
//	设置对手死亡时所执行的函数
void set_when_enemy_dead(function f)
{
	when_enemy_dead = functionp(f) ? f : 0;
}
//	获取对手受到攻击时所执行的函数指针
function get_when_enemy_be_hit()
{
	return when_enemy_be_hit;
}
//	设置对手受到攻击时所执行的函数指针
void set_when_enemy_be_hit(function f)
{
	when_enemy_be_hit = functionp(f) ? f : 0;
}
//	获取当前NPC 的外形编号
int get_char_picid()
{
	return 0501;
}
int get_id_color() { return 0x800080; }
//	构造函数
void create()
{
	set_name("Hổ Vương");
	set_char_type(FIGHTER_TYPE);
	setup();
}
/*--------------------------------------回调----------------------------------------------*/
int can_fight(object who)
{
	object owner;
	string leader, id;
	if (who->is_npc() && objectp(owner = who->get_owner()))
	{
		who = owner;
	}
	if (who->is_npc())
	{
		set_enemy(0);
		return 0;
	}
	if (who->get_enemy() == this_object())
	{
		return 1;
	}
	if (who->get_number() != get("enemy"))
	{
		return 0;
	}
	return 1;
}
// 	是否可以被攻击
int can_be_fighted(object who)
{
	object owner;
	string leader, id;
	if (who->get_enemy() == this_object())
	{
		return 1;
	}
	if (owner = who->get_owner())
	{
		who = owner;
	}
	if (who->is_npc())
	{
		return 0;
	}
	if (who->get_number() == get("enemy"))
	{
		if (who->get_save("guess_true_tiger_fight"))
		{
			if (who->get_save("guess_true_tiger_fight") == getoid(this_object()))
			{
				canfight = 1;
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			who->set_save("guess_true_tiger_fight", getoid(this_object()));
			canfight = 1;
			return 1;
		}
	}
	else
	{
		send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), get_name() + ": \n   Ngươi nói xem ta là Hổ Vương thật hay giả?");
		return 0;
	}
}
void heart_beat_walk()
{
	object who, *member_list = ({});
	object npc = this_object();
	if (canfight)
	{
		member_list = get_range_object_2(npc, npc->get_max_seek(), USER_TYPE);
		if (sizeof(member_list) > 0)
		{
			foreach (who in member_list)
			{
				if (objectp(who))
				{
					if (who->is_die())
					{
						continue;
					}
					if (!npc->can_fight(who) || !who->can_be_fighted(npc))
					{
						continue;
					}
					npc->set_main_enemy(who);
					::heart_beat_walk();
					return;
				}
			}
			canfight = 0;
		}
	}
	::heart_beat_walk();
}
//	函数：死亡奖励
void win_bonus(object who)
{
	__FILE__->win_bonus_callout(this_object(), who);
}
//	死亡奖励的回调函数
void win_bonus_callout(object me, object who)
{
	mixed tigers_id;
	object item, owner;
	int i, size;
	string tiger_oid;
	canfight = 0;
	if (owner = who->get_owner())
	{
		who = owner;
	}
	tigers_id = who->get("guess_true_tiger_tigers");
	tiger_oid = sprintf("%x#", getoid(me));
	for (i = 0, size = sizeof(tigers_id); i < size; i++)
	{
		if (tiger_oid == tigers_id[i])
		{
			if (!who->get_save("guess_true_tiger"))
			{
				who->set_save("guess_true_tiger", 1);
			}
			else
			{
				who->set_save("guess_true_tiger", who->get_save("guess_true_tiger") + 1);
			}
			break;
		}
	}
	who->set("guess_true_tiger_nojump", 0);
	GUESS_TRUE_TIGER->delete_tigers_on_player(who, FALL_ACT);
	ACTIVE_ANGEL_NPC->do_next_stage(who);
}
/*-------------------------------------------------------------------------------------*/
