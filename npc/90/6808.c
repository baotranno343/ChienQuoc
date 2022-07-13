
#include <npc.h>
#include <equip.h>
#include <skill.h>
#include <cmd.h>
#include <ansi.h>

inherit OFFICER;

// 函数：获取门派名称
string get_fam_name() { return "Côn Luân"; }

// 函数：获取人物造型
int get_char_picid() { return 700; }

// 函数：获取门派顺序
int get_fam_order() { return 5; }

void do_info();
void accept_task(string arg) ;

// 函数：构造处理
void create()
{
        set_name( "Thạch Sư" );
        set_2( "talk", ([
                "info"          : (: do_info :),
                "accept_task"          : (: accept_task :),
        ]));        
        setup();
}

void do_info()
{
        object player, master;
        player = this_player();
        master = this_object();
        send_user( player, "%c%s", ':', sprintf("%s：\n你可以到城里问问酒店的老板，他是万事通，没什么不知道的。", master->get_name() ) );
}

// 函数：点击出现界面
void do_look( object who ) { TASK_MASTER_D->do_look_quest9( who, this_object() ); }

// 接收心爱物品
int accept_object( object player, object obj ) 
{
	object who = this_object();
	return TASK_MASTER_D->accept_object2( who, player, obj ); 
}

int accept_money(object who, int gold)
{
	return TASK_MASTER_D->accept_money(this_object(), who, gold);
}

void accept_task( string arg ) { TASK_MASTER_D->accept_task9( this_player(), this_object(),arg ); }