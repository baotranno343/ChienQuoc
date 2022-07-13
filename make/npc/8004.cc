
// 自动生成：/make/npc/make8004

#include <npc.h>
#include <city.h>

#define INTERIOR_D      "/inh/city/interior"

inherit OFFICER;

void do_build( string arg );
void do_upgrade( string arg );
void do_plant( string arg );
void do_food( string arg );

// 函数：获取人物造型
int get_char_picid() { return %04d; }

// 函数：构造处理
void create()
{
        set_name("%s");
        set_city_name("%s");

        set_2( "talk", ([
                "build"         : (: do_build :),
                "upgrade"       : (: do_upgrade :),
                "plant"         : (: do_plant :),
                "food"          : (: do_food:),
        ]) );

        setup();
}

string get_master() { return %s->get_master(); }
string get_master_2() { return %s->get_master_2(); }
string get_master_3() { return %s->get_master_3(); }

void do_look( object who ) { INTERIOR_D->do_look( who, this_object() ); }

void do_build( string arg ) { INTERIOR_D->do_build( this_player(), this_object(), arg ); }
void do_upgrade( string arg ) { INTERIOR_D->do_upgrade( this_player(), this_object(), arg ); }
void do_plant( string arg ) { INTERIOR_D->do_plant( this_player(), this_object(), arg ); }
void do_food( string arg ) { INTERIOR_D->do_food( this_player(), this_object(), arg ); }

int accept_object( object who, object obj ) { return INTERIOR_D->accept_object( who, this_object(), obj ); }
