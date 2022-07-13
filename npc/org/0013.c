
#include <npc.h>
#include <ansi.h>
#include <city.h>
#include <effect.h>

inherit OFFICER;
inherit SAVE_F;
//inherit "/inh/char/group";

void do_info( string arg );
void do_skill( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5502; }

// 函数：构造处理
void create()
{
        object me = this_object();
        int time;        
        
        set_name( "Thiên Cơ Viện Chủ " );

        set_2( "talk", ([
                "info"          : (: do_info :),
                "skill"         : (: do_skill :),
        ]) );

        setup();
}

void do_look( object who ) { "/sys/sys/manager"->do_look_5( who, this_object() ); }
void do_info( string arg ) { "/sys/sys/manager"->do_info_5( this_player(), this_object(), arg ); }
void do_skill( string arg )
{
	object target;
	target = this_object()->get("orgnpc");
	if (!objectp(target)) return;
	"/sys/city/manager3"->do_skill( this_player(), target, arg );
}