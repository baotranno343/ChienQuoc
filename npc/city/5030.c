
// 自动生成：/make/npc/make8020
#include <ansi.h>
#include <npc.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 5801; }

void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Nông phu Lưu Kê Đàn");
        set_city_name("Tần Quốc");
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));          
        setup(); 
}

void do_look( object who )
{
	"/sys/user/plant"->do_look(who, this_object());
}

void do_welcome( string arg )
{
        object me, who;
        me = this_object();
        who = this_player();
        "/sys/user/plant"->do_welcome(who, me, arg);
}       