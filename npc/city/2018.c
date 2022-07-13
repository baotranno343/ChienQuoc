
// 自动生成：/make/npc/make8018

#include <npc.h>
#include <city.h>

#define AGENT_D         "/inh/city/agent"

inherit OFFICER;

void do_job( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5301; }

// 函数：构造处理
void create()
{
        set_name("Chức Nghiệp Kinh Kì");
        set_city_name("Hàn Quốc");

        set_2( "talk", ([
                "job"           : (: do_job :),
        ]) );

        setup();
}

string get_master() { return CITY_HAN->get_master(); }
string get_master_2() { return CITY_HAN->get_master_2(); }
string get_master_3() { return CITY_HAN->get_master_3(); }

void do_look( object who ) { AGENT_D->do_look( who, this_object() ); }

void do_job( string arg ) { AGENT_D->do_job( this_player(), this_object(), arg ); }
