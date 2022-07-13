
// 自动生成：/make/npc/make8010

#include <npc.h>
#include <city.h>

#define GUARDER_D       "/inh/city/guarder"

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return %04d; }

// 函数：构造处理
void create()
{
        set_name("%s");
        set_city_name("%s");

        setup();
}

string get_master() { return %s->get_master(); }
string get_master_2() { return %s->get_master_2(); }
string get_master_3() { return %s->get_master_3(); }

void do_look( object who ) { GUARDER_D->do_look_3( who, this_object() ); }
