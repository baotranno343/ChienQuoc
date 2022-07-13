
#include <equip.h>
#include <effect.h>

inherit TALISMAN;

// 函数：法宝识别
int get_talisman_type() { return 10; }

// 函数：构造处理
void create()
{
        object me = this_object();

        set_name( "Truyện Thế Bảo Ngọc" );
        set_picid_1(9591);
        set_picid_2(9591);
        set_unit( "块" );

        set_level(3);
        set_value(20000);
        set_max_lasting(18099);

        setup();

        if( !clonep(me) ) return;

        set_heart_timer( me, set_heart_timer_2(me, getoid(me) % 10) );    // 心跳随机
        set_heart_loop(me, 150);    // 循环心跳：１５秒钟
        me->heart_beat();
        set_heart_beat(1);
}

// 函数：获取描述
string get_desc() 
{ 
        return "Tự động hồi phục Khí Huyết và Pháp Lực";
}

// 函数：心跳处理
void heart_beat() { }

// 函数：心跳处理(循环)
void heart_beat_loop( int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8 ) { __FILE__ ->heart_beat_loop_callout( this_object(), effect1, effect2, effect3, effect4, effect5, effect6, effect7, effect8 ); }

// 函数：心跳处理(循环)(在线更新)
void heart_beat_loop_callout( object me, int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8 )    // 每１５秒处理
{
        object owner;

        if( objectp( owner = me->get_owner() ) || objectp( owner = environment() ) )
        {
                if( !get_effect(owner, EFFECT_CHAR_SUPPRESS) && owner->get_equip(HAND_TYPE) == me )
                {
                        if( !owner->is_die() ) 
                        {
                                owner->add_hp( owner->get_max_hp() * 5 / 100 );
                                owner->add_mp( owner->get_max_mp() * 5 / 100 );
                        }
                }
        }
}
