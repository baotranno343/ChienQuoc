
// 自动生成：/make/npc/make8003

#include <npc.h>
#include <city.h>

#define FINANCE_D       "/inh/city/finance"
#define FINANCE_2_D     "/inh/city/finance2"
#define JOB_TRADER_D    "/inh/job/trader"

inherit OFFICER;

void do_info( string arg );
void do_tax( string arg );
void do_salary( string arg );
void do_cheque( string arg );
void do_comput( string arg );

// 函数：获取人物造型
int get_char_picid() { return %04d; }

// 函数：构造处理
void create()
{
        set_name("%s");
        set_city_name("%s");

        set_2( "talk", ([
                "info"          : (: do_info :),
                "tax"           : (: do_tax :),
                "salary"        : (: do_salary :),
                "cheque"        : (: do_cheque :),
                "comput"        : (: do_comput :),
        ]) );

        setup();
}

string get_master() { return %s->get_master(); }
string get_master_2() { return %s->get_master_2(); }
string get_master_3() { return %s->get_master_3(); }

void do_look( object who ) { FINANCE_D->do_look( who, this_object() ); }

void do_info( string arg ) { FINANCE_D->do_info( this_player(), this_object(), arg ); }
void do_tax( string arg ) { FINANCE_D->do_tax( this_player(), this_object(), arg ); }
void do_salary( string arg ) { FINANCE_D->do_salary( this_player(), this_object(), arg ); }

void do_cheque( string arg ) { JOB_TRADER_D->do_cheque( this_player(), this_object(), arg ); }    // ## 3 ##
void do_comput( string arg ) { FINANCE_2_D->do_comput( this_player(), this_object(), arg ); }    // ## 2 ##
