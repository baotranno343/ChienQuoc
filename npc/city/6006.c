
// 自动生成：/make/npc/make8006

#include <npc.h>
#include <city.h>

#define INQUISITOR_D    "/inh/city/inquisitor"

inherit OFFICER;

void do_elect( string arg );
void do_vote( string arg );
void do_score( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5102; }

// 函数：构造处理
void create()
{
        set_name("Sở Quốc Ngự Sử");
	set_real_name("Ngô Khởi");
        set_city_name("Sở Quốc");

        set_2( "talk", ([
                "elect"         : (: do_elect :),
                "vote"          : (: do_vote :),
                "score"         : (: do_score :),
        ]) );

        setup();
}

string get_master() { return CITY_CHU->get_master(); }
string get_master_2() { return CITY_CHU->get_master_2(); }
string get_master_3() { return CITY_CHU->get_master_3(); }

void do_look( object who ) { INQUISITOR_D->do_look( who, this_object() ); }

void do_elect( string arg ) { INQUISITOR_D->do_elect( this_player(), this_object(), arg ); }
void do_vote( string arg ) { INQUISITOR_D->do_vote( this_player(), this_object(), arg ); }
void do_score( string arg ) { INQUISITOR_D->do_score( this_player(), this_object(), arg ); }
