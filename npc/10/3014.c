
// 自动生成：/make/npc/make-collect

#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <task.h>
#include <music.h>

inherit OFFICER;

void do_task();

// 函数：获取人物造型
int get_char_picid() { return 7302; }

// 函数：构造处理
void create()
{
        set_name("Tú Lệ Tiểu Tỷ");

        set_2( "talk", ([
                "task"          : (: do_task :),
        ]));      

        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";

        tmp += CHAIN_D->get_chain_menu(who,this_object());
        send_user( who, "%c%s", ':', sprintf( "%s：\n    %s\n", get_name(),TASK_COLLECT_D->get_talk_string(0411))
        + tmp +
        ESC"离开"
         );
}

// 函数：任务处理
void do_task()
{
        object me, who;
        int life;

        me = this_object();  who = this_player();

        if( who->get_level() >= 30 )
        {
                life = who->get_reincarnation();

                if(     !who->get_legend(TASK_COLLECT_04, 11)
                ||     ( life >= 1 && who->get_legend(TASK_COLLECT_04, 12) && !who->get_legend(TASK_COLLECT_04, 13) )
                ||     ( life >= 2 && who->get_legend(TASK_COLLECT_04, 14) && !who->get_legend(TASK_COLLECT_04, 15) ) )
                {
                        send_user( who, "%c%s", ':', sprintf( "%s：\n%s\n", get_name(), TASK_COLLECT_D->get_talk_string(0413) ) );
                        if( !who->get_legend(TASK_COLLECT_04, 11) ) who->set_legend(TASK_COLLECT_04, 11);
                        else if( !who->get_legend(TASK_COLLECT_04, 13) ) who->set_legend(TASK_COLLECT_04, 13);
                        else if( !who->get_legend(TASK_COLLECT_04, 15) ) who->set_legend(TASK_COLLECT_04, 15);
                        USER_TASK_D->auto_give_task(who);
                        return;
                }
        }
}
