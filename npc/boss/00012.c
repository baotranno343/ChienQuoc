
// 自动生成：/make/npc/makenpc

#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit SLAVE;
// 函数：是否不能进城
int cannot_enter_city() { return 1; }
// 函数：获取人物造型
int get_char_picid() { return 0350; }
// 函数：获取召唤兽类型
int get_zombie_type() { return 99; }     // 判断种类
int is_tigerking_slave() { return 1; }

int is_zombie() { return 0; }  

// 函数：构造处理
void create()
{
        set_name("Lang Yêu Thủ Vệ");

        set_level(90);
	set_max_hp(35000);
	set_ap(1250);
	set_dp(400);
	set_cp(100);
	set_pp(500);
	set_sp(550);
	set_walk_speed(3);
	set_attack_speed(15);
        set_max_seek(8);
        set_head_color(0x398c);

        setup();
        set_char_type(FIGHTER_TYPE_2);  
}

// 函数：死亡奖励
void win_bonus( object who ) { __FILE__ ->win_bonus_callout( this_object(), who ); }

// 函数：死亡奖励(在线更新)
void win_bonus_callout( object me, object who )
{
	int p,size,i;
	object owner,*team;
	
        if( owner = who->get_owner() ) who = owner;
        if( who->is_npc() ) return ;

	who->add_exp(4000);

        if( who->get_leader() && arrayp( team = who->get_team() ) && sizeof(team) > 1 )
        {
                team = me->correct_bonus_team(team);
                size = sizeof(team);
        }
        else    size = 1;
        	
        if ( size == 1 )
     		who->add_potential(20);
	else
	{
		for( i = 0; i < size; i ++ ) if( team[i] )
                	team[i]->add_potential(20);	
		
	}
        	
}
