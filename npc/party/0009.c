#include <npc.h>
#include <ansi.h>
#include <public.h>

inherit OFFICER;
// 函数：获取人物造型
int get_char_picid() { return 0011; }
int get_id_color() { return 0xdd0571; }
void do_welcome(string arg);
int is_yutu() { return 1; }
// 函数：构造处理
void create()
{
        set_name("小兔子");
        set_2( "talk", ([
                 "welcome"         : (: do_welcome :),
        ]) );

        setup();
}
