#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <effect.h>
#include <action.h>

inherit SLAVE;

int get_max_level0() { return 3;}

// 函数：获取召唤兽类型
int get_zombie_type() { return ZOMBIE_TYPE_1; }     // 判断种类

// 函数：构造处理
void create()
{
        set_name( "Đao Vương" );
        set_char_picid(9966);

        setup();
}

// 函数：获取装备代码
int get_weapon_code() { return UNARMED; }

// --------------------------------------------------------------- 远程调用 ----

// 函数：升级处理
void upgrade_level( int level ) { __FILE__ ->upgrade_level_callout( this_object(), level ); }

// 函数：升级处理(在线更新)
void upgrade_level_callout( object me, int level )
{
        switch( level )
        {
      default : me->set_char_type(SLAVE_TYPE_1);
                break;
       case 2 : me->set_char_type(SLAVE_TYPE_2);
                break;
       case 3 : me->set_char_type(SLAVE_TYPE_3);
                break;
        }
        me->set_attack_speed(10);
        me->set_walk_speed(2);
        me->set_walk_step(2);
}

// 函数：升级处理
void upgrade_level_2( int level ) { __FILE__ ->upgrade_level_2_callout( this_object(), level ); }

// 函数：升级处理(在线更新)
void upgrade_level_2_callout( object me, int level )
{
        object owner;
        int hp, cp, pp;

        if( level > 1 ) if( objectp( owner = me->get_owner() ) && owner->is_user() )
        {
                cp = owner->get_cp();
                pp = owner->get_pp();
                me->add_max_hp( 100000 );  
                me->set_hp(me->get_max_hp());
                me->set_mp(me->get_max_mp());
                me->add_ap( 10000 );
                me->add_dp( 7000 );
                me->add_pp( 7000 );
                me->add_sp( 2000 );
        }
}

void do_after_attack(object who)
{
	object me = this_object();
	object * user;
	int level, level0, rate;
	level = me->get_level_2();
	level0 = me->get_level_0();
	rate = 75+ (level0-40)/150*100;
	if (random(100)<rate && !get_effect(who, EFFECT_CHAR_FAINT_0))
       {
                user = get_scene_object_2(who, USER_TYPE);
                set_effect(who, EFFECT_CHAR_FAINT, 2);    // 小心准备 me
                if( get_heart_state(who) == MAGIC_STAT ) send_user( user, "%c%d%d%c", 0x40, getoid(who), time2(), MAGIC_ACT_END );    // 结束施法动作               
                send_user( who, "%c%w%w%c", 0x81, 9002, get_effect_3(who, EFFECT_CHAR_FAINT), EFFECT_BAD );
                send_user( user - ({ who }), "%c%d%w%c%c", 0x83, getoid(who), 9002, 1, EFFECT_BAD );
                send_user( user, "%c%d%w%c%c%c", 0x6f, getoid(who), 9002, 10, OVER_BODY, PF_LOOP );
        }
}