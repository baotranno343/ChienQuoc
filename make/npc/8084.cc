
// 自动生成：/make/npc/make8084

#include <npc.h>

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