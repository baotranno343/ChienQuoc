
// 自动生成：/make/npc/make8008

#include <npc.h>
#include <city.h>

#define WARDER_D        "/inh/city/warder"

inherit OFFICER;

void do_faling();
void accept_task();

// 函数：获取人物造型
int get_char_picid() { return 5102; }

// 函数：构造处理
void create()
{
        set_name("Sở Quốc Giám Ngục Quan");
        set_city_name("Sở Quốc");

        set_2( "talk", ([
                "faling"        : (: do_faling :),
                 "accept_task"	: (: accept_task :),
        ]) );

        setup();
}

string get_master() { return CITY_CHU->get_master(); }
string get_master_2() { return CITY_CHU->get_master_2(); }
string get_master_3() { return CITY_CHU->get_master_3(); }

void do_look( object who ) { WARDER_D->do_look( who, this_object() ); }

void do_faling() { WARDER_D->do_faling( this_player(), this_object() ); }

void accept_task() { WARDER_D->accept_task( this_player(), this_object() );}