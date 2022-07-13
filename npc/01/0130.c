
#include <npc.h>
#include <ansi.h>
#include <task.h>
#include <music.h>

inherit OFFICER;

void do_fight();

// 函数：获取人物造型
int get_char_picid() { return 5901; }

// 函数：构造处理
void create()
{
        set_name( "Mã Lão Hán" );

        set_2( "talk", ([
                "fight"         : (: do_fight :),
        ]));

        setup();
}

// 函数：对话处理
void do_look( object who )
{
        string cmd,tmp="";
        int level, gold, exp;
/*
        if( who->get_level() == 26 )
        {
                if( !who->get_legend(TASK_NEWBIE_02, 1) )
                {
                        cmd = sprintf( "talk %x# fight\n", getoid( this_object() ) );
                        send_user( who, "%c%s", ':', get_name() + "：\n昨天我教训了几只山鸡，结果野兔也找上门来偷东西吃，我想过几天它们还会来，您能帮我除掉它们吗？\n" 
                                ESC "没问题。\n" + cmd +
                                ESC "离开。\nCLOSE\n" );
                        return;
                }
                else if( !who->get_legend(TASK_NEWBIE_02, 2)
                ||      !who->get_legend(TASK_NEWBIE_02, 3)
                ||      !who->get_legend(TASK_NEWBIE_02, 4)
                ||      !who->get_legend(TASK_NEWBIE_02, 5)
                ||      !who->get_legend(TASK_NEWBIE_02, 6)
                ||      !who->get_legend(TASK_NEWBIE_02, 7)
                ||      !who->get_legend(TASK_NEWBIE_02, 8)
                ||      !who->get_legend(TASK_NEWBIE_02, 9)
                ||      !who->get_legend(TASK_NEWBIE_02, 10)
                ||      !who->get_legend(TASK_NEWBIE_02, 11)
                ||      !who->get_legend(TASK_NEWBIE_02, 12)
                ||      !who->get_legend(TASK_NEWBIE_02, 13)
                ||      !who->get_legend(TASK_NEWBIE_02, 14)
                ||      !who->get_legend(TASK_NEWBIE_02, 15)
                ||      !who->get_legend(TASK_NEWBIE_02, 16) )
                {
                        send_user( who, "%c%s", ':', get_name() + "：\n您教训完野兔了吗？\n" );
                        return;
                }
                else if( !who->get_legend(TASK_NEWBIE_02, 17) )
                {
                        send_user( who, "%c%s", ':', who->get_name() + "：\n我教训完野兔啦。\n\n" +
                                get_name() + "：\n谢谢您了，真是为民除害的大英雄啊。\n" );

                        who->set_legend(TASK_NEWBIE_02, 17);
                        level = who->get_level();
                        gold = level * 500;  who->add_cash(gold);  who->add_gold_log("task", gold);
                        exp = level * level * level * 4;  who->add_exp(exp);

                        send_user( who, "%c%w", 0x0d, MUSIC_TASK );
                        write_user( who, ECHO "您完成新手任务，金钱 %+d, 经验 %+d。", gold, exp );

                        return;
                }
        }
*/        
        tmp += CHAIN_D->get_chain_menu(who,this_object());
        send_user( who, "%c%s", ':', get_name() + "：\n自从教训了野兔后，它们就很少到村子里偷东西吃啦。\n"
        +tmp +
        ESC"离开" );
}

// 函数：对话处理
void do_fight()
{
        object me, who;

        me = this_object();  who = this_player();
/*
        if( who->get_level() == 26 )
        {
                if( !who->get_legend(TASK_NEWBIE_02, 1) )
                {
                        send_user( who, "%c%s", ':', get_name() + "：\n他们在野外，请帮忙去教训教训野兔吧。\n" );
                        who->set_legend(TASK_NEWBIE_02, 1);
                        USER_TASK_D->auto_give_task(who);
                        return;
                }
        }
*/        
}
