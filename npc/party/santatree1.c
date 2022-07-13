#include <npc.h>
#include <ansi.h>
#include <public.h>

inherit OFFICER;
// 函数：获取人物造型
int get_char_picid() { return 2701; }
void do_welcome(string arg);
// 函数：构造处理
void create()
{
        set_name("");

        setup();
}


void do_look(object who)
{
}
