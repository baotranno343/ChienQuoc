
// 自动生成：/make/npc/make0001

#include <npc.h>
#include <cmd.h>

inherit OFFICER;

// 函数：当铺老板
int is_banker() { return 1; }

// 函数：获取人物造型
int get_char_picid() { return %04d; }

// 函数：构造处理
void create()
{
        set_name("%s");

        setup();
}

// 函数：对话处理
void do_look( object who )
{
        PAWN_CMD->main( who, sprintf( "%%x# %%d", getoid( this_object() ), 0 ) );    // who->get("pawn#") + 1
}
