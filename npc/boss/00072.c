#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <effect.h>
#include <action.h>

inherit SLAVE;
int cannot_enter_city() { return 1; }

// 函数：获取召唤兽类型
int get_zombie_type() { return ZOMBIE_TYPE_1; }     // 判断种类

// 函数：构造处理
void create()
{
        set_name( "Cương Thi" );
        set_char_picid(4134);
	set_attack_speed(10);
        set_walk_speed(2);
        set_walk_step(2);
        set_head_color(0x2);
        setup();
}

// 函数：获取装备代码
int get_weapon_code() { return UNARMED; }

// --------------------------------------------------------------- 远程调用 ----


void do_after_attack(object who)
{
	object me = this_object();
	object * user;
	int level, level0, rate;

	if (random(100)<5)
       	{
                who->set_poison(30);
                set_effect_2(who, EFFECT_CHAR_POISON, 10, 2);
                send_user( who, "%c%w%w%c", 0x81, 9096, get_effect_3(who, EFFECT_CHAR_POISON), EFFECT_BAD );
                send_user( get_scene_object_2(who, USER_TYPE) - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9096, 1, EFFECT_BAD );
        }
}

// 函数：死亡奖励
void win_bonus( object who ) { __FILE__ ->win_bonus_callout( this_object(), who ); }

// 函数：死亡奖励(在线更新)
void win_bonus_callout( object me, object who )
{
	int level,level2,exp=100;
	object owner;
	
        if( owner = who->get_owner() ) who = owner;
        if( who->is_npc() ) return ;

	level = me->get_level();
	level2 = level - who->get_level();
	exp = me->correct_exp_bonus(level, level2, exp) * who->get_online_rate() / 100;
	who->add_exp(exp);
}
