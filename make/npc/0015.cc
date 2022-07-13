
// 自动生成：/make/npc/make0015

#include <npc.h>
#include <ansi.h>

inherit OFFICER;

void do_info();

// 函数：获取人物造型
int get_char_picid() { return %04d; }

// 函数：构造处理
void create()
{
        set_name("%s");

      set_2( "talk", ([
                "info"  : (: do_info :),
        ]));    

        setup();
}

// 函数：对话处理
void do_look( object who )
{
        object me = this_object(), map;
        int type, x, y, z, p, i;
        string result, name;
        type = who->get_save_2("mastertask.type");
        if (type==4||type==5)
        {
                TASK_MASTER_D->do_look_0015(me, who);              
                return;                           
        }                                
        TASK_COLLECT_D->do_talk( this_player(), this_object() );
        
}

// 函数：住宿处理
void do_info()
{
        object me, who;
        string result, info;
        me = this_object();  who = this_player();
        TASK_MASTER_D->do_info(me, who);             
}

