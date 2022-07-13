
#include <npc.h>
#include <ansi.h>
#include <city.h>
#include <effect.h>

inherit OFFICER;
inherit SAVE_F;
//inherit "/inh/char/group";

void do_back( string arg );
void do_info( string arg );
void do_travel( string arg );
void do_travel2( string arg );
void do_join( string arg );

// 函数：获取人物造型
int get_char_picid() { return 9955; }

// 函数：构造处理
void create()
{
        object me = this_object();
        int time;        
        set_city_name("Hàn Quốc");
        
        set_name( "Bang Phái Tổng Quản "+get_city_name() );

        set_2( "talk", ([
                "back"          : (: do_back :),
                "info"          : (: do_info :),
                "travel"        : (: do_travel :),
                "travel2"       : (: do_travel2 :),
                "join"          : (: do_join :),
        ]) );

        setup();
}

void do_look( object who ) { "/sys/sys/manager"->do_look_1( who, this_object() ); }

void do_back( string arg ) { "/sys/sys/manager"->do_back( this_player(), this_object(), arg ); }
void do_info( string arg ) { "/sys/sys/manager"->do_info( this_player(), this_object(), arg ); }
void do_travel( string arg ) { "/sys/sys/manager"->do_travel( this_player(), this_object(), arg ); }
void do_travel2( string arg ) { "/sys/sys/manager"->do_travel2( this_player(), this_object(), arg ); }
void do_join( string arg ) { "/sys/sys/manager"->do_join( this_player(), this_object(), arg ); }