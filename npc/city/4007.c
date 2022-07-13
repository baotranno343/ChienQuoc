
// 自动生成：/make/npc/make8007

#include <npc.h>
#include <city.h>

#define DIPLOMAT_D      "/inh/city/diplomat"

inherit OFFICER;

void do_relation( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5102; }

// 函数：构造处理
void create()
{
        set_name("Ngụy Quốc Sử Tiết");
	set_real_name("Ngu Khanh");
        set_city_name("Ngụy Quốc");

        set_2( "talk", ([
                "relation"      : (: do_relation :),
        ]) );

        setup();
}

string get_master() { return CITY_WEI->get_master(); }
string get_master_2() { return CITY_WEI->get_master_2(); }
string get_master_3() { return CITY_WEI->get_master_3(); }

void do_look( object who ) { DIPLOMAT_D->do_look( who, this_object() ); }

void do_relation( string arg ) { DIPLOMAT_D->do_relation( this_player(), this_object(), arg ); }
