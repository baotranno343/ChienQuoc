
// 自动生成：/make/npc/make8020

#include <npc.h>

#define INTERIOR_D      "/inh/city/interior"

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

// 函数：对话处理
void do_look( object who )
{
        more_look_menu( who, sprintf( "%%s：\n    %%s\n", get_name(), "/quest/word"->get_country_word(this_object()) ) );
}

int accept_object( object who, object obj ) { return INTERIOR_D->accept_object_2( who, this_object(), obj, %d ); }
