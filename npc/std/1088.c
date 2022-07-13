
#include <npc.h>
#include <cmd.h>

inherit OFFICER;

// 函数：小贩识别
int is_seller_2() { return 1; }

// 函数：构造处理
void create()
{
        object me = this_object();

        set_name("采药夫");
        NPC_EQUIP_D->init_figure( this_object(), FARMER, MALE, 20 );
        set_city_name("新手村");

        set_2( "good", ([
                "01" : "/item/91/9120",    // 救急丹
                "02" : "/item/91/9121",    // 活心丹
                "03" : "/item/91/9125",    // 再造丸
                "04" : "/item/91/9140",    // 辟毒散
        ]) );
        set_2( "list", ([
                "01" : 20,
                "02" : 20,
                "03" : 10,
                "04" : 20,
        ]) );

        setup();

        set( "birthday", time() );

        if( !clonep(me) ) return;

        set_heart_timer( me, set_heart_timer_2(me, getoid(me) % 10) );    // 心跳随机
        set_heart_loop(me, 600);    // 循环心跳：１分钟
        me->heart_beat();
        set_heart_beat(1);
}

// 函数：对话处理
void do_look( object who )
{
        LIST_CMD->main( who, sprintf( "%x#", getoid( this_object() ) ) );
}

// -------------------------------------------------------------

// 函数：心跳处理
void heart_beat() { }

private static int HeartSec = 0;        // 心跳计时

// 函数：获取心跳计时
int get_heart_sec() { return HeartSec; }

// 函数：设置心跳计时
int set_heart_sec( int point ) { return HeartSec = point; }

// 函数：增添心跳计时
int add_heart_sec( int point ) { return set_heart_sec(HeartSec + point); }

// 函数：心跳处理(循环)
void heart_beat_loop( int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8 ) { __FILE__ ->heart_beat_loop_callout( this_object(), effect1, effect2, effect3, effect4, effect5, effect6, effect7, effect8 ); }

// 函数：心跳处理(循环)(在线更新)
void heart_beat_loop_callout( object me, int effect1, int effect2, int effect3, int effect4, int effect5, int effect6, int effect7, int effect8 )    // 每１分处理
{
        object who;
        mapping good;

        if( me->add_heart_sec(1) > 5 )    // ５分后处理以下
        {
                me->remove_from_scene();
                destruct(me);
                return;
        }

        if( mapp( good = me->get_2("good") ) && !sizeof( keys(good) ) )
        {
                me->remove_from_scene();
                destruct(me);
                return;
        }
}
