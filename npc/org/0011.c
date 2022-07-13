
#include <npc.h>
#include <ansi.h>
#include <city.h>
#include <effect.h>

inherit OFFICER;
inherit SAVE_F;
//inherit "/inh/char/group";

void do_info( string arg );

// 函数：获取人物造型
int get_char_picid() { return 9306; }

// 函数：构造处理
void create()
{
        object me = this_object();
        int time;        
        
        set_name( "Võ Giáo Đầu" );

        set_2( "talk", ([
                "info"          : (: do_info :),
        ]) );

        setup();
}

void do_look( object who ) { "/sys/sys/manager"->do_look_3( who, this_object() ); }
void do_info( string arg ) { "/sys/sys/manager"->do_info_3( this_player(), this_object(), arg ); }
