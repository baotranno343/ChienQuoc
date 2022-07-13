// 自动生成：/make/npc/make-biao

#include <npc.h>
#include <ansi.h>
#include <task.h>
#include <public.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 9715; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Mạnh Tử");
        set_city_name("Chu Quốc");

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),

        ]));      

        setup();
}

// 函数：对话处理
void do_look( object who ) { TEACHER_D->do_look( who, this_object() ); }

void do_welcome( string arg )
{
        object me = this_object();
        TEACHER_D->do_welcome(me,this_player(),arg);
}
