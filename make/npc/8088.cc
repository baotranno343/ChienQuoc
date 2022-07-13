
// 自动生成：/make/npc/make8088

#include <npc.h>

#define JOB_TRADER_D    "/inh/job/trader"

inherit OFFICER;
inherit "/inh/npc/trader";

void reset();
void do_good( string arg );

// 函数：获取人物造型
int get_char_picid() { return %04d; }

// 函数：构造处理
void create()
{
        set_name("%s");
        set_city_name("%s");

        set_2( "talk", ([
                "good"          : (: do_good :),
        ]) );
        reset();

        setup();
}

// 函数：复位处理
void reset()
{
        set_buy_rate( random(1001) );
        set_sell_rate( random(1001) );

        set_2( "good", ([
                "01" : %s,
                "02" : %s,
                "03" : %s,
        ]) );
        set_2( "list", ([
                "01" : %d,
                "02" : %d,
                "03" : %d,
        ]) );
}

void do_look( object who ) { JOB_TRADER_D->do_look( who, this_object() ); }

void do_good( string arg ) { JOB_TRADER_D->do_good( this_player(), this_object(), arg ); }
