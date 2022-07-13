#include <npc.h>
#include <ansi.h>
#define MARRY_D  "sys/user/marry"
inherit OFFICER;

void do_welcome(string arg);
void do_qixi(string arg);

// 函数：获取人物造型
int get_char_picid() { return 5403; }

// 函数：构造处理
void create()
{
        set_name( "Nguyệt Lão" );

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
		"qixi"             : (: do_qixi :),
        ]));

        setup();
}

// 函数：对话处理
void do_look( object who )
{
	MARRY_D->do_look(this_object(),who);
}

void do_welcome(string arg) {MARRY_D->do_welcome(this_object(),this_player(),arg);}
void do_qixi(string arg) {"sys/party/qixi"->do_qixi(this_object(),this_player(),arg);}