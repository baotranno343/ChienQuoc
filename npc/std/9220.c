
#include <equip.h>

inherit OFFICER;

void do_look( object who ) { "/inh/job/farmer"->do_look_2( who, this_object() ); }
void do_fish( string arg ) { "/inh/job/farmer"->do_fish( this_player(), this_object(), arg ); }

// 函数：构造处理
void create()
{
        set_name( "" );    // 捕捞渔夫
        set_gender(1);

        set_2( "talk", ([
                "fish"          : (: do_fish :),
        ]));

        setup();
}

// 函数：获取装备代码
int get_armor_code() { return X_JOBS; }

// 函数：获取头发代码
int get_head_code() { return 30; }
