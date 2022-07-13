
#include <npc.h>
#include <ansi.h>

inherit OFFICER;

void do_task_start();
void do_task_cancel();
void accept_task();
void join_task();
void task_info();
void task_bonus();
void do_visit(string arg);

// 函数：获取人物造型
int get_char_picid() { return 5105; }

// 函数：构造处理
void create()
{
        set_name( "Sư Gia" );
	set_real_name("Từ Phúc");

        set_2( "talk", ([
                "task"          : (: do_task_start :),
//                "cancel"        : (: do_task_cancel :),
                "accept"	: (: accept_task :),
                "join"		: (: join_task :),
                "info"		: (: task_info :),
                "bonus"		: (: task_bonus :),
                "visit"		: (: do_visit :),
        ]));      
        set("level", 30);
//        set("legend", ({ 32 }));
//	set("mpLegend",([30:({32,}),]));

        setup();
        set("mpLegend",([0:({32,}),]));
}

// 函数：对话处理
void do_look( object who ) { TASK_ROBBER_D->do_look( who, this_object() ); }

// 函数：开始任务
void do_task_start() { TASK_ROBBER_D->do_task_start( this_player(), this_object() ); }
// 函数：取消任务
void do_task_cancel() { TASK_ROBBER_D->do_task_cancel( this_player(), this_object() ); }
// 函数：取消任务
void accept_task() { TASK_ROBBER_D->accept_task( this_player(), this_object() ); }
// 函数：加入任务
void join_task() { TASK_ROBBER_D->join_task( this_player(), this_object() ); }
// 函数：任务信息
void task_info() { TASK_ROBBER_D->task_info( this_player(), this_object() ); }
// 函数：任务信息
void task_bonus() { TASK_ROBBER_D->task_bonus( this_player(), this_object() ); }

void do_visit(string arg)	{ TASK_ROBBER_D->do_visit( this_player(), this_object() ,arg); }