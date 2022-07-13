#include <npc.h>
#include <ansi.h>
#define MARRY_D  "sys/user/marry"
inherit OFFICER;

void do_welcome(string arg);

// 函数：获取人物造型
int get_char_picid() { return 9409; }

// 函数：构造处理
void create()
{
        set_name( "Hồng Nương" );

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));

        setup();
}

// 函数：对话处理
void do_look( object who )
{
	MARRY_D->do_look1(this_object(),who);
}

void do_welcome(string arg) {MARRY_D->do_welcome1(this_object(),this_player(),arg);}
