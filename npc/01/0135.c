
#include <npc.h>
#include <ansi.h>
#include <task.h>
#include <music.h>

inherit OFFICER;
void do_welcome(string arg);

// 函数：获取人物造型
int get_char_picid() { return 5901; }

// 函数：构造处理
void create()
{
        set_name( "Khổng Lão Đầu" );
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));
//        set("level", 0);
//        set("legend", ({ 32*2+26 }));
	set("mpLegend2",([5:({32*40+21,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
        string tmp="";

/*        if( who->get_level() >= 5 && !who->get_legend(TASK_NEWBIE_02, 27) )
        {
		tmp = sprintf(ESC"乱蛰人的小蜜蜂\ntalk %x# welcome.1\n",getoid(this_object()));
        }*/
        if( who->get_legend(TASK_40, 20) && !who->get_legend(TASK_40, 21) )
        {
		tmp += sprintf(ESC +HIY+ "孤独\ntalk %x# welcome.4\n",getoid(this_object()));
        }
        tmp += CHAIN_D->get_chain_menu(who,this_object());
        send_user( who, "%c%s", ':', get_name() + "：\n自从教训了稻草人后，他们没敢再来了，但是最近有很多小蜜蜂乱蛰人，也挺讨厌的！\n"
        	+ tmp +
        	ESC"离开"
         );
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
	int flag,i,j,k,size,p;
	object who,item,*inv;
	
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
	case 1:
		if( who->get_level() >= 5 && !who->get_legend(TASK_NEWBIE_02, 26) )
			send_user(who,"%c%s",':',sprintf("%s:\n    看看我周围这些小蜜蜂，以前挺和善的，可最近不知道怎么搞的，像着了魔一样，经常成群结队的攻击周围的行人、百姓，这事恐怕有蹊跷，但是当务之急是得尽快地消灭掉他们。你来得正好，出发吧！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开",me->get_name(),getoid(me)));
		else if ( who->get_save_2("xiaomifeng") < 8 )
			send_user(who,"%c%s",':',sprintf("%s:\n    奇怪？这么久了你还没有消灭掉他们？难道他们的毒性与攻击力又提升了？这可增加了难度，你得尽快呀！\n"ESC"离开",me->get_name()));
		else 
			send_user(who,"%c%s",':',sprintf("%s:\n    其实你杀死这几只小蜜蜂也只是杯水车薪，最重要的还是抓出那个幕后黑手，但是单凭你一人的力量是不太可能的。这事还得从长计议。你先拿了这些奖励吧！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开",me->get_name(),getoid(me)));
			break;
	case 2:
		if( who->get_level() >= 5 && !who->get_legend(TASK_NEWBIE_02, 26) )
		{
			who->set_legend(TASK_NEWBIE_02, 26);
			who->delete_save_2("xiaomifeng");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YEWAI,"清溪" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YEWAI,2,"乱蛰人的小蜜蜂" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"乱蛰人的小蜜蜂");	
		}
		break;	
	case 3:
		if ( who->get_legend(TASK_NEWBIE_02, 26) && !who->get_legend(TASK_NEWBIE_02, 27) && who->get_save_2("xiaomifeng") >= 8 )
		{
			item = new("item/91/9140");
			item->set_amount(5);
			p = item->move(who,-1);
			if ( !p )
			{
				send_user(who,"%c%s",'!',"你身上的东西太多");
				destruct(item);
				return;
			}
			who->delete_save_2("xiaomifeng");
			item->add_to_user(p);
			who->add_exp(370);
			who->add_potential(30);
			who->add_cash(2000);
			who->set_legend(TASK_NEWBIE_02, 27);
			send_user(who,"%c%s",';',"乱蛰人的小蜜蜂 经验 370 潜能 30 金钱 2000 辟毒散 5");			
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YEWAI,2,"" );
		}
		break;		
	case 4:
		if( who->get_legend(TASK_40, 20) && !who->get_legend(TASK_40, 21) )
			send_user(who,"%c%s",':',sprintf("%s:\n    是他？！天啦，我已经快30年没有见到他了，我得赶快去会会我这位老友。\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开",me->get_name(),getoid(me)));
		break;
	case 5:
		if( who->get_legend(TASK_40, 20) && !who->get_legend(TASK_40, 21) )
		{
			if (TASK_LEGEND_D->check_task_item(who,"叙旧信",1) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
			who->add_exp(200);
			who->add_potential(30);
			who->add_cash(1000);
			who->set_legend(TASK_40, 21);
			send_user(who,"%c%s",';',"孤独 经验 200 潜能 30 金钱 1000");			
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,34,"" );
		}
		break;	
	}
}