
// 自动生成：/make/npc/make-collect

#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <task.h>
#include <music.h>

inherit OFFICER;

void do_task();

// 函数：获取人物造型
int get_char_picid() { return %04d; }

// 函数：构造处理
void create()
{
        set_name("%s");

        set_2( "talk", ([
                "task"          : (: do_task :),
        ]));      

        setup();
}

// 函数：对话处理
void do_look( object who )
{
        object item1, item2, item3, item4, item5, item6, item7, item8, item9, item10;
        object item11, item12, item13, item14, item15, item16, item17, item18, item19, item20;
        string file, cmd;
        int z, p, life, exp, pot, gift;

        if( who->get_level() >= 30 )
        {
                life = who->get_reincarnation();

                if(     !who->get_legend(TASK_COLLECT_%02d, %d)
                ||     ( life >= 1 && who->get_legend(TASK_COLLECT_%02d, %d) && !who->get_legend(TASK_COLLECT_%02d, %d) )
                ||     ( life >= 2 && who->get_legend(TASK_COLLECT_%02d, %d) && !who->get_legend(TASK_COLLECT_%02d, %d) ) )
                {
                        cmd = sprintf( "talk %%x# task\n", getoid( this_object() ) );
                        send_user( who, "%%c%%s", ':', sprintf( "%%s：\n%%s\n", get_name(), TASK_COLLECT_D->get_talk_string(%04d) ) +
                                ESC "没问题。\n" + cmd +
                                ESC "离开。\nCLOSE\n" );
                        return;
                }
                else if( ( who->get_legend(TASK_COLLECT_%02d, %d) && !who->get_legend(TASK_COLLECT_%02d, %d) )
                ||    ( life >= 1 && who->get_legend(TASK_COLLECT_%02d, %d) && !who->get_legend(TASK_COLLECT_%02d, %d) )
                ||    ( life >= 2 && who->get_legend(TASK_COLLECT_%02d, %d) && !who->get_legend(TASK_COLLECT_%02d, %d) ) )
                {
                        if(     %s
                                 )
                        {
%s

                                send_user( who, "%%c%%s", ':', sprintf( "%%s：\n%%s\n", get_name(), TASK_COLLECT_D->get_talk_string(%04d) ) );

                                if( !who->get_legend(TASK_COLLECT_%02d, %d) ) who->set_legend(TASK_COLLECT_%02d, %d);
                                else if( !who->get_legend(TASK_COLLECT_%02d, %d) ) who->set_legend(TASK_COLLECT_%02d, %d);
                                else if( !who->get_legend(TASK_COLLECT_%02d, %d) ) who->set_legend(TASK_COLLECT_%02d, %d);
                                exp = %d;  who->add_exp(exp);
                                pot = %d;  who->add_potential(pot);
                                gift = %d;  who->add_gift_point(gift);

                                send_user( who, "%%c%%w", 0x0d, MUSIC_TASK );
                                write_user( who, ECHO "您完成收集任务，经验 %%+d, 潜能 %%+d, 道行 %%+d。", exp, pot, gift );

                                z = get_z(who);

                                if( random(100) < %d ) if( load_object( file = "/item/std/8900" ) )    // 得到宝石碎片
                                {
                                        item1 = new( file );
                                        if( p = item1->move(who, -1) ) 
                                        {
                                                item1->add_to_user(p);
                                                write_user(who, ECHO "由于您的努力，意外得到一%%s%%s。", item1->get_unit(), item1->get_name() );
                                        }
                                        else if( p = get_valid_xy( z, get_x(who), get_y(who), IS_ITEM_BLOCK) )
                                        {
                                                item1->add_to_scene(z, p / 1000, p %% 1000);
                                                write_user(who, ECHO "由于您的努力，意外得到一%%s%%s。", item1->get_unit(), item1->get_name() );
                                        }
                                        else    destruct(item1);
                                }

                                if( random(100) < %d ) if( load_object( file = STONE_FILE->get_stone_file() ) )    // 得到宝石
                                {
                                        item1 = new( file );
                                        if( p = item1->move(who, -1) ) 
                                        {
                                                item1->add_to_user(p);
                                                write_user(who, ECHO "由于您的努力，意外得到一%%s%%s。", item1->get_unit(), item1->get_name() );
                                        }
                                        else if( p = get_valid_xy( z, get_x(who), get_y(who), IS_ITEM_BLOCK) )
                                        {
                                                item1->add_to_scene(z, p / 1000, p %% 1000);
                                                write_user(who, ECHO "由于您的努力，意外得到一%%s%%s。", item1->get_unit(), item1->get_name() );
                                        }
                                        else    destruct(item1);
                                }

                                if( random(100) < %d ) if( load_object( file = BOOK_FILE->get_book_file() ) )    // 得到进阶书籍
                                {
                                        item1 = new( file );
                                        if( p = item1->move(who, -1) ) 
                                        {
                                                item1->add_to_user(p);
                                                write_user(who, ECHO "由于您的努力，意外得到一%%s%%s。", item1->get_unit(), item1->get_name() );
                                        }
                                        else if( p = get_valid_xy( z, get_x(who), get_y(who), IS_ITEM_BLOCK) )
                                        {
                                                item1->add_to_scene(z, p / 1000, p %% 1000);
                                                write_user(who, ECHO "由于您的努力，意外得到一%%s%%s。", item1->get_unit(), item1->get_name() );
                                        }
                                        else    destruct(item1);
                                }

                                return;
                        }
                        else
                        {
                                send_user( who, "%%c%%s", ':', sprintf( "%%s：\n%%s\n", get_name(), TASK_COLLECT_D->get_talk_string(%04d) ) );
                                return;
                        }
                }
                else
                {
                        send_user( who, "%%c%%s", ':', sprintf( "%%s：\n%%s\n", get_name(), TASK_COLLECT_D->get_talk_string(%04d) ) );
                        return;
                }
        }
        send_user( who, "%%c%%s", ':', sprintf( "%%s：\n%%s\n", get_name(), TASK_COLLECT_D->get_talk_string(%04d) ) );
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

                if(     !who->get_legend(TASK_COLLECT_%02d, %d)
                ||     ( life >= 1 && who->get_legend(TASK_COLLECT_%02d, %d) && !who->get_legend(TASK_COLLECT_%02d, %d) )
                ||     ( life >= 2 && who->get_legend(TASK_COLLECT_%02d, %d) && !who->get_legend(TASK_COLLECT_%02d, %d) ) )
                {
                        send_user( who, "%%c%%s", ':', sprintf( "%%s：\n%%s\n", get_name(), TASK_COLLECT_D->get_talk_string(%04d) ) );
                        if( !who->get_legend(TASK_COLLECT_%02d, %d) ) who->set_legend(TASK_COLLECT_%02d, %d);
                        else if( !who->get_legend(TASK_COLLECT_%02d, %d) ) who->set_legend(TASK_COLLECT_%02d, %d);
                        else if( !who->get_legend(TASK_COLLECT_%02d, %d) ) who->set_legend(TASK_COLLECT_%02d, %d);
                        USER_TASK_D->auto_give_task(who);
                        return;
                }
        }
}
