// 自动生成：/make/npc/make-biao

#include <npc.h>
#include <ansi.h>
#include <task.h>
#include <public.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 9512; } //9312
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Mạc Địch");
        set_real_name("Huynh Đệ Tổng Quản");

        set_2("talk", (["welcome":(
                                      : do_welcome:),

        ]));

        setup();
}

// 函数：对话处理
void do_look(object who) { "sys/user/huynhde"->do_look(who, this_object()); }

void do_welcome(string arg)
{
        object me = this_object();
        "sys/user/huynhde"->do_welcome(me, this_player(), arg);
}
