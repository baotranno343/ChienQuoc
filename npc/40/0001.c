#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <task.h>
#include <equip.h>

inherit OFFICER;

void do_welcome(string arg);

// 函数：获取人物造型
int get_char_picid() { return 7302; }

// 函数：构造处理
void create()
{
        set_name("寻儿");

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));      
	set("mpLegend2",([0:({32*23+29,32*24+3,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
        tmp += CHAIN_D->get_chain_menu(who,this_object());
        if ( who->get_legend(TASK_23,28)&&!who->get_legend(TASK_23,29) ) 
		tmp += sprintf(ESC HIY "丈夫的信\ntalk %x# welcome.1\n",getoid(this_object())); 
        if ( (who->get_legend(TASK_23,29)&&!who->get_legend(TASK_24,1)) || (who->get_legend(TASK_24,1)&&!who->get_legend(TASK_24,3)) ) 
		tmp += sprintf(ESC HIY "慢性相思病\ntalk %x# welcome.1\n",getoid(this_object())); 
		
        send_user( who, "%c%s", ':', sprintf( "%s：\n    他是在我们新婚之夜被抓走的，整整10年，我们没有再见一面，他知道，我一直在等着他，直到他回来。\n", get_name())
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
        int flag,p;
        object who,item,obj;  
        string cmd1;
       	string *nTmp,tmp;     
           
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
       		if (who->get_legend(TASK_23,28)&&!who->get_legend(TASK_23,29))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    10年了！终于有他的消息了！以前虽然一直没有他任何消息，但是我相信他总有一天会荣归故里，和我团聚的。这些日子赵讯那恶棍逼得我走投无路，我都已经想寻死几次了，幸好有你替我除掉这个恶棍，现在我可以安心养好身体，一定要等到我的相公回来这一天。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if (who->get_legend(TASK_23,29)&&!who->get_legend(TASK_24,1))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    最近这些日子我身子好象特别差，郎中说我相思过度，再加上赵讯哪个恶棍逼害，抑郁成疾，要是这样下去的话，还等不到我相公回来，我的身体就要垮下去。郎中给我开了个药方，上面说要在弯道上找的心莲、冬虫草、金银花这三味草药才可以把我的病治好，但是弯道那里现在到处都是贼匪，我根本没办法去那里找这三味草药，你可以再帮我这个忙吗？\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
		else if (who->get_legend(TASK_24,1)&&!who->get_legend(TASK_24,2))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    弯道是一个很危险的地方，收集草药的时候你一定要小心啊。为了我相公，我一定要好好活下去！\n"ESC"离开", me->get_name()));
		else if (who->get_legend(TASK_24,2)&&!who->get_legend(TASK_24,3))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    有了这些草药，我就可以把我的身体调理好，然后在这里等着我的相公衣锦还乡了。你可是我们夫妇的大恩人，我也不知道该怎么报答你好，这里是我的一点小心意，希望你对你还有点用。\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
        case 2:
        	if ( who->get_legend(TASK_23,28) && !who->get_legend(TASK_23,29) )
        	{
			if ( TASK_LEGEND_D->check_task_item(who,"给寻儿的家书",1) != 1 )
				return ;
			TASK_LEGEND_D->task_finish(who);
			TASK_LEGEND_D->give_item(who,"item/product/64128",1);
			who->set_legend(TASK_23,29);
			who->add_exp(20000);
			who->add_potential(290);
			who->add_cash(20000);
			send_user(who,"%c%s",';',"武士的爱情（3） 经验 20000 潜能 290 金钱 20000 混天冠图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,40,"" );
       		}
        	break;
	case 3:
        	if ( who->get_legend(TASK_23,29)&&!who->get_legend(TASK_24,1) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_24,1);
        		who->delete_save_2("xercuanxinlian");
        		who->delete_save_2("xerdongcongcao");
        		who->delete_save_2("xerjinyinhua");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"韩国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,29,"武士的爱情（4）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"武士的爱情（4）");
        	}
        	break;  
        case 4:
        	if (who->get_legend(TASK_24,2)&&!who->get_legend(TASK_24,3))
        	{
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),70,WAIST_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
        		if (TASK_LEGEND_D->check_task_item(who,"穿心莲",5) != 1 )
        			return;
        		if (TASK_LEGEND_D->check_task_item(who,"冬虫草",5) != 1 )
        		{
        			item = new("item/98/0110");
        			item->set_amount(5);
        			p = item->move(who,-1);
        			item->add_to_user(p);
        			return;
        		}
        		if (TASK_LEGEND_D->check_task_item(who,"金银花",8) != 1 )
        		{
        			item = new("item/98/0110");
        			item->set_amount(5);
        			p = item->move(who,-1);
        			item->add_to_user(p);
        			item = new("item/98/0111");
        			item->set_amount(5);
        			p = item->move(who,-1);
        			item->add_to_user(p);        			
        			return;        			
        		}
			TASK_LEGEND_D->task_finish(who);
			TASK_LEGEND_D->give_item(who,tmp,1);
			who->set_legend(TASK_24,3);
        		who->delete_save_2("xercuanxinlian");
        		who->delete_save_2("xerdongcongcao");
        		who->delete_save_2("xerjinyinhua");
			who->add_exp(56000);
			who->add_potential(830);
			who->add_cash(57000);
			send_user(who,"%c%s",';',sprintf("武士的爱情（4） 经验 56000 潜能 830 金钱 57000 %s 1",tmp->get_name()));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,29,"" );
        	}
        	break;
        }
}