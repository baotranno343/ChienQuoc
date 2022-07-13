
#include <npc.h>
#include <ansi.h>

inherit OFFICER;

void do_goto( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5403; }

// 函数：获取门派名称
string get_fam_name() { return "Vân Mộng Cốc"; }

// 函数：获取升级顺序
int get_fam_order() { return 6; }

// 函数：构造处理
void create()
{
        set_name("Y Sư");
        set_real_name("Xa Phu");

        set_2( "talk", ([
                "go"   : (: do_goto :),
        ]));

        setup();
}

// 函数：对话处理
void do_look( object who )
{
	"/sys/task/travel"->do_look2(this_object(), who);        
}

// 函数：移动处理
void do_goto( string  arg )
{
	"/sys/task/travel"->do_goto2(this_object(), this_player(), arg);     
}
/*
// 函数：对话处理
void do_look( object who )
{
        object me = this_object();
        if (me->get_fam_name()!=who->get_fam_name())
        {
                send_user(who, "%c%s", ':', sprintf("%s：\n%s\n", me->get_name(), "/quest/master"->get_answer(me->get_fam_name(), me->get_fam_order())) );
                return ;
        }                
        more_look_menu( who, get_name() + "：\n这位" + NPC_RANK_D->get_respect(who) + "想回周国吗？\n"
                ESC "好的。\n"     + sprintf( "talk %x# go\n", getoid( this_object() ) ) +
                ESC "离开。\nCLOSE\n" );
}
*/