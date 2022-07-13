
#include <ansi.h>
#include <equip.h>
#include <action.h>
#include <effect.h>

inherit TALISMAN;

// 函数：生效几率
int get_active_rate() { return 100; }

// 函数：恢复比率
int get_revive_rete() { return 80; }

// 函数：准备时间
int get_time_interval() { return 600; }

// 函数：法宝识别
int get_talisman_type() { return 9; }

// 函数：构造处理
void create()
{
        object me = this_object();

        set_name( "招魂幡" );
        set_picid_1(9581);
        set_picid_2(9581);
        set_unit( "块" );

        set_level(3);
        set_value(20000);
        set_max_lasting(1099);

        setup();

        if( !clonep(me) ) return;

        set_heart_timer( me, set_heart_timer_2(me, getoid(me) % 10) );    // 心跳随机
        set_heart_loop(me, 100);    // 循环心跳：１０秒钟
        me->heart_beat();
        set_heart_beat(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "免死，相当于自己被其他玩家救活";
}

private static int HeartSec = 0;        // 心跳计时

// 函数：获取心跳计时
int get_heart_sec() { return HeartSec; }

// 函数：设置心跳计时
int set_heart_sec( int point ) 
{ 
        object who;

        point = range_value( point, 0, get_time_interval() ); 

        if(     HeartSec != point
        &&    ( objectp( who = get_owner() ) || objectp( who = environment() ) ) )
                send_user( who, "%c%d%c", 0x31, getoid( this_object() ), 0 );    // 更新描述

        return HeartSec = point; 
}

// 函数：增添心跳计时
int add_heart_sec( int point ) { return set_heart_sec(HeartSec + point); }

// 函数：心跳处理
void heart_beat() { }

// 函数：心跳处理(循环)
void heart_beat_loop( int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8 ) { __FILE__ ->heart_beat_loop_callout( this_object(), effect1, effect2, effect3, effect4, effect5, effect6, effect7, effect8 ); }

// 函数：心跳处理(循环)(在线更新)
void heart_beat_loop_callout( object me, int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8 )    // 每１０秒处理
{
        object owner;

        if( objectp( owner = me->get_owner() ) || objectp( owner = environment() ) )    // 获取主人对象
        {
                if( !get_effect(owner, EFFECT_CHAR_SUPPRESS) && owner->get_equip(HAND_TYPE) == me )    // 正在装备之中
                {
                        if( me->add_heart_sec(10) >= me->get_time_interval() )    // 进入生效状态
                        {
                                if( owner->is_die() )    // random(100) < me->get_active_rate()
                                {
                                        set_effect(owner, EFFECT_USER_DIE, 0);
                                        owner->set_die(0);
                                        owner->set_hp( owner->get_max_hp() * me->get_revive_rete() / 100 );

                                        write_user( owner, ECHO HIY "招魂幡" ECHO "将您救了起来。" );

                                        owner->set_login_flag(2);    // 跳转保护
                                        set_invisible(owner, 1);
                                        set_effect(owner, EFFECT_USER_LOGIN, 2);

                                        me->add_lasting(-1);    // 使用减少耐久
                                        me->set_heart_sec(0);    // 初始化时间(准备状态)
                                }
                        }
                }
        }
}
