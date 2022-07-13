
#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>
#include <action.h>

inherit SLAVE;

// 函数：是否不能进城
int cannot_enter_city() { return 1; }
// 函数：获取人物造型
int get_char_picid() { return 650; }
// 函数：获取召唤兽类型
int get_zombie_type() { return 99; }     // 判断种类

int is_zombie() { return 0; }  

// 函数：构造处理
void create()
{
        set_name("Binh Sĩ");

	set_walk_speed(3);
	set_attack_speed(20);
        set_max_seek(8);

        setup();
        set_char_type(FIGHTER_TYPE);  
}

// 函数：死亡奖励
void win_bonus( object who ) 
{
	int exp;
	object	owner = who->get_owner();
	if ( owner && owner->is_user() )
		who = owner;
	exp = NPC_ENERGY_D->get_exp_bonus(get_level());
	exp = exp * who->get_online_rate() / 100;
	who->add_exp(exp);
}

int can_fight( object who ) 
{
	object owner;
	
	owner =  get_owner();
	if ( !owner )
		return 0;				
       return owner->can_fight(who);
}

int can_be_fighted( object who ) 
{
	object owner;
	
	owner =  get_owner();
	if ( !owner )
		return 0;				
       return owner->can_be_fighted(who);
}

void heart_beat_walk()
{
	object owner,me;
	
	owner = get_owner();
	if ( !owner && get_z(me = this_object()) )
	{
		me->remove_from_scene(FALL_ACT);
		destruct(me);
		return ;
	}
	::heart_beat_walk();
}