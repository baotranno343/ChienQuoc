
#include <npc.h>
#include <ansi.h>
#include <city.h>
#include <effect.h>

inherit OFFICER;
inherit SAVE_F;
//inherit "/inh/char/group";

#define CITY_MANAGER_D          "/sys/city/manager"
#define CITY_MANAGER_2_D        "/sys/city/manager2"
#define CITY_MANAGER_3_D        "/sys/city/manager3"
#define CITY_MANAGER_4_D        "/sys/city/manager4"
#define CITY_MANAGER_5_D        "/sys/city/manager5"

void do_info( string arg );

void do_appoint( string arg );
void do_demise( string arg );
void do_banish( string arg );
void do_exit( string arg );

void do_apply( string arg );
void do_accept( string arg );
void do_refuse( string arg );

void do_note( string arg );

void do_war( string arg );
void do_org( string arg );
void do_quest( string arg );
void do_upgrade( string arg );

// 函数：获取人物造型
int get_char_picid() { return 9955; }

// 函数：构造处理
void create()
{
        object me = this_object();

        set_name( "Bang phái Tổng Quản" );

        set_2( "talk", ([
                "info"          : (: do_info :),
                "appoint"       : (: do_appoint :),
                "demise"        : (: do_demise :),
                "banish"        : (: do_banish :),
                "exit"          : (: do_exit :),
                "apply"         : (: do_apply :),
                "accept"        : (: do_accept :),
                "refuse"        : (: do_refuse :),
                "note"          : (: do_note :),
                "war"           : (: do_war :),
                "org"           : (: do_org :),                
                "quest"         : (: do_quest :),                
                "upgrade"       : (: do_upgrade :),        
        ]) );

        setup();
}

void do_look( object who ) { "/sys/sys/manager"->do_look_2( who, this_object() ); }

void do_upgrade( string arg ) { "/sys/sys/manager"->do_upgrade( this_player(), this_object(), arg ); }

void do_quest( string arg ) { "/sys/sys/manager"->do_quest( this_player(), this_object(), arg ); }

void do_info( string arg )
{
	object target;
	target = this_object()->get("orgnpc");
	if (!objectp(target)) return;
	CITY_MANAGER_D->do_info( this_player(), target, arg );
}

void do_appoint( string arg )
{
	object target;
	target = this_object()->get("orgnpc");
	if (!objectp(target)) return;
	CITY_MANAGER_D->do_appoint( this_player(), target, arg );
}

void do_demise( string arg )
{
	object target;
	target = this_object()->get("orgnpc");
	if (!objectp(target)) return;
	CITY_MANAGER_D->do_demise( this_player(), target, arg );
}

void do_banish( string arg )
{
	object target;
	target = this_object()->get("orgnpc");
	if (!objectp(target)) return;
	CITY_MANAGER_D->do_banish( this_player(), target, arg );
}

void do_exit( string arg )
{
	object target;
	target = this_object()->get("orgnpc");
	if (!objectp(target)) return;
	CITY_MANAGER_D->do_exit( this_player(), target, arg );
}

void do_apply( string arg )
{
	object target;
	target = this_object()->get("orgnpc");
	if (!objectp(target)) return;
	CITY_MANAGER_2_D->do_apply( this_player(), target, arg );
}

void do_accept( string arg )
{
	object target;
	target = this_object()->get("orgnpc");
	if (!objectp(target)) return;
	CITY_MANAGER_2_D->do_accept( this_player(), target, arg );
}

void do_refuse( string arg )
{
	object target;
	target = this_object()->get("orgnpc");
	if (!objectp(target)) return;
	CITY_MANAGER_2_D->do_refuse( this_player(), target, arg );
}

void do_note( string arg )
{
	object target;
	target = this_object()->get("orgnpc");
	if (!objectp(target)) return;
	CITY_MANAGER_4_D->do_note( this_player(), target, arg );
}

void do_war( string arg )
{
	object target;
	target = this_object()->get("orgnpc");
	if (!objectp(target)) return;
	CITY_MANAGER_5_D->do_war( this_player(), target, arg );
}

void do_org( string arg )
{
	object target;
	target = this_object()->get("orgnpc");
	if (!objectp(target)) return;
	CITY_MANAGER_5_D->do_org( this_player(), target, arg );
}

void do_qest( object who ) { "/sys/sys/manager"->do_qest( who, this_object() ); }