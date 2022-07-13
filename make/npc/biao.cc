
// 自动生成：/make/npc/make-biao

#include <npc.h>
#include <ansi.h>

inherit OFFICER;

void do_task_start();
void do_task_cancel();

// 函数：获取人物造型
int get_char_picid() { return %04d; }

// 函数：构造处理
void create()
{
        set_name("%s");
        set_city_name("%s");

%s      set_2( "talk", ([
                "task"          : (: do_task_start :),
                "cancel"        : (: do_task_cancel :),
        ]));    %s

        setup();
}

// 函数：对话处理
%s void do_look( object who ) { TASK_ESCORT_D->do_look( who, this_object() ); }
%s void do_look( object who ) { TASK_ESCORT_D->do_look_2( who, this_object() ); }

// 函数：开始任务
%s void do_task_start() { TASK_ESCORT_D->do_task_start( this_player(), this_object() ); }
// 函数：取消任务
%s void do_task_cancel() { TASK_ESCORT_D->do_task_cancel( this_player(), this_object() ); }
