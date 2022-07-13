#include <npc.h>
#include <city.h>

#define WORLDCUP	"sys/party/worldcup"

inherit OFFICER;

void do_choice(string arg);
void do_bet(string arg);
void do_bonus();

// 函数：获取人物造型
int get_char_picid() { return 5302; }

// 函数：构造处理
void create()
{
        set_name("竞猜使者");
        set_city_name("新手村");

        set_2( "talk", ([
                "choice"        : (: do_choice :),
               	 "bet"       : (: do_bet :),
                 "bonus"         : (: do_bonus :),
        ]) );

        setup();
}

void do_look( object who ) { WORLDCUP->do_look(who,this_object(),1); }

void do_choice(string arg) { WORLDCUP->do_choice(this_player(),this_object(),arg,1); }

void do_bet(string arg) { WORLDCUP->do_bet(this_player(),this_object(),arg,1); }

void do_bonus() { WORLDCUP->get_bonus(this_player(),this_object()); }