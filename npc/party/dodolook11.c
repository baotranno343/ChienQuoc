#include <ansi.h>
#include <npc.h>
#include <equip.h>
#include <action.h>

inherit SLAVE;
int iWalk;
// 函数：获取召唤兽类型
int get_zombie_type() { return 99; }     // 判断种类
// 函数：是否不能进城
int cannot_enter_city() { return 1; }

// 函数：构造处理
void create()
{
        set_name( "打手" );
        set_char_picid(8000);    // 蒙面人
	
        setup();

        set( "birthday", time() );
}

void win_bonus( object who ) 
{
	int exp,level1,level2;
	object owner;

	if( owner = who->get_owner() ) who = owner;
        if( who->is_npc() ) return;
        	
	owner = get_owner();
	if ( !objectp(owner) )
		return ;

	owner->add("dodolook.slave",-1);

	level1 = get_level();
	level2 = who->get_level();
	exp = correct_exp_bonus(level1,level1-level2,50);
	who->add_exp(exp);
	who->add_potential(1);	
	tell_user( who, "您击毙%s，经验 %+d, 潜能 %+d。", get_name(), exp, 1 );		
}

void heart_beat_walk()
{
	string robber;
	object *member,who,enemy;

	if ( (iWalk++)%3 )
	{
		::heart_beat_walk();
		return;
	}
	if ( iWalk>2&&!objectp(get_owner() ) )
	{
		remove_from_scene(FALL_ACT);
		destruct(this_object());
		return ;
	}
	member = get_range_object_2(this_object(),get_max_seek(), USER_TYPE);
	member -= ({ 0 });
	if ( sizeof(member) != 0 )
	{
		foreach(who in member)
		{
			if ( can_fight(who) != 1 )
				continue;
			set_main_enemy(who);
			::heart_beat_walk();
			return;
		}		
	}
	set_enemy(0);
}

// 函数：可以接受战斗
int can_be_fighted( object who ) 
{ 
        object owner;

	owner = get_owner();
	if ( !owner )
		return 0;
	return owner->can_be_fighted(who);
}

int can_fight( object who ) 
{ 
        object owner;

	owner = get_owner();
	if ( !owner )
		return 0;
	return owner->can_fight(who);
}