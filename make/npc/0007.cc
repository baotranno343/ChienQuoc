
// 自动生成：/make/npc/make0007

#include <npc.h>
#include <cmd.h>

inherit OFFICER;

// 函数：修理师傅
int is_repairer() { return 1; }

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
        REPAIR_CMD->main( who, sprintf( "%%x#", getoid( this_object() ) ) );
}
