
#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 0010; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Tiểu Kê Cô Cô");
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));
//	set("mpLegend",([0:({32*2+7,}),]));
// 	set("mpLegend2",([0:({32*2+9,}),]));
       setup();
}

// 函数：对话处理
void do_look( object who )
{
        int id = getoid( this_object() );
        
//	if (!who->get_legend(TASK_NEWBIE_02, 7)||!who->get_legend(TASK_NEWBIE_02, 8)||!who->get_legend(TASK_NEWBIE_02, 9))
//        {
//                 send_user( who, "%c%c%w%s", ':',3,get_char_picid(), sprintf(get_name() + "：\n    咕咕！咕咕！咕～\n"ESC HIY "小鸡咕咕的饲料\ntalk %x# welcome.1\n"ESC"离开",id));
//                 return;
//        }               

        send_user( who, "%c%s", ':', " " + get_name() + ":cô cô! cô cô! cô! !\n");
}

//int accept_object( object who, object item )
//{
//        if (item->get_name()=="麦子"&&who->get_level()>=1)
//        {
//                if (!who->get_legend(TASK_NEWBIE_00, 17) )
//                {
//                        who->set_legend(TASK_NEWBIE_00, 17);
//                        send_user( who, "%c%s", ':', get_name() + "：“咕咕！咕！咕～”\n    “咕～咕～咕咕！”\n  小鸡十分高兴地吃起了你给它的麦子。");
//                        who->add_exp(30);
//                        send_user( who, "%c%s", '!', "你获得了30点经验。" );
//                        return 1;
//                }                        
//        }        
//}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
	int flag,p;
	object who,item;
	
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        	case 1:
        		if (!who->get_legend(TASK_NEWBIE_02, 7) )
        			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s:\n    咕咕！咕！咕～（肚子好饿）\n    咕咕～（正北方）咕咕～咕！（刘大叔）咕叽～咕叽！（有好吃的饲料）\n"ESC"领取任务\ntalk %x# welcome.2\n"ESC"离开",me->get_name(),getoid(me)));
        		else if (!who->get_legend(TASK_NEWBIE_02, 8) )
				send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s:\n    叽叽咕～（好饿）\n    咕叽叽！（饲料呢？）\n"ESC"离开",me->get_name(),));
			else if (!who->get_legend(TASK_NEWBIE_02, 9) )
        			send_user(who,"%c%c%w%s",':',3,me->get_char_picid(),sprintf("%s:\n    咕咕叽～（谢谢）\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开",me->get_name(),getoid(me)));
        		break;
		case 2:
			if (who->get_legend(TASK_NEWBIE_02, 7) )
				return;
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			who->set_legend(TASK_NEWBIE_02, 7);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"新手村" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,16,"小鸡咕咕" );
			send_user( who, "%c%s", '!', "你接受了"HIY"小鸡咕咕"NOR"任务");			
			break;
		case 3:
			if (!who->get_legend(TASK_NEWBIE_02, 7)||!who->get_legend(TASK_NEWBIE_02, 8)||who->get_legend(TASK_NEWBIE_02, 9) )
				return;
			if (TASK_LEGEND_D->check_task_item(who,"小鸡饲料",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);		
			item = new("item/32/3282");
			item->set_amount(5);
			p = item->move(who,-1);
			if ( !p )
			{
				send_user(who,"%c%s",'!',"你身上的东西太多了");				
				return ;
			}
			item->add_to_user(p);			
			who->set_legend(TASK_NEWBIE_02, 9);
			who->add_exp(100);
			send_user(who,"%c%s",';',"小鸡咕咕 经验 100 桔子 5");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,16,"" );
			break;        		
        }	
}