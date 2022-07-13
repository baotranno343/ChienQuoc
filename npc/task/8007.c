#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <task.h>
#include <ansi.h>

inherit SLAVE;
// 函数：是否不能进城
int cannot_enter_city() { return 1; }
// 函数：获取人物造型
int get_char_picid() { return 0101; }
// 函数：获取召唤兽类型
int get_zombie_type() { return 99; }     // 判断种类
//int is_general_slave() { return 1; }
int get_id_color() { return 4904; }

int is_zombie() { return 0; }  

// 函数：构造处理
void create()
{
        set_name("狂犬");
        setup();
        set_walk_speed(2);
        set_attack_speed(10);
        set_walk_step(2);          
        set_char_type(FIGHTER_TYPE);  
}

// 函数：特技攻击对手
int perform_action( object who ) 
{
	return "skill/11/11008"->perform_action_npc(this_object(),who);
}

// 函数：判断可以战斗
int can_fight( object who ) 
{
	object owner;
	if( objectp(owner=who->get_owner()) && owner->is_npc() ) return 0;
	return ::can_fight(who);	
}