
// 自动生成：/make/npc/make-collect

#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <task.h>
#include <music.h>

inherit OFFICER;

void do_task();

// 函数：获取人物造型
int get_char_picid() { return 5505; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Lí Đức");

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));      
	set("mpLegend2",([0:({32*33+26,32*33+29,32*34+3,32*37+22,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	int id;
	string tmp="";

	id = getoid(this_object());
        tmp += CHAIN_D->get_chain_menu(who,this_object());
        if ( who->get_legend(TASK_33,25) && !who->get_legend(TASK_33,26) ) 
		tmp += sprintf(ESC HIY "打探消息\ntalk %x# welcome.1\n",id); 
        if ( ( who->get_legend(TASK_33,26) && !who->get_legend(TASK_33,27) ) || ( who->get_legend(TASK_33,27) && !who->get_legend(TASK_33,29) ) )
		tmp += sprintf(ESC HIY "证明实力\ntalk %x# welcome.1\n",id); 
        if ( ( who->get_legend(TASK_33,29) && !who->get_legend(TASK_34,1) ) || ( who->get_legend(TASK_34,1) && !who->get_legend(TASK_34,3) ) )
		tmp += sprintf(ESC HIY "接受请求\ntalk %x# welcome.1\n",id); 
        if ( who->get_legend(TASK_34,3) && !who->get_legend(TASK_34,4) )
		tmp += sprintf(ESC HIY "寻宝历险\ntalk %x# welcome.1\n",id); 
        if ( who->get_level() >= 25 && who->get_legend(TASK_37,21) && !who->get_legend(TASK_37,22) )
		tmp += sprintf(ESC HIY "家庭聚会\ntalk %x# welcome.8\n",id); 

        send_user( who, "%c%s", ':', sprintf( "%s：\n    %s\n", get_name(),TASK_COLLECT_D->get_talk_string(0011))
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
        int flag,i,size,p,amount;
        object who,item, *inv;     
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_legend(TASK_33,25) && !who->get_legend(TASK_33,26) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呵呵，你也是听了市井流言来找我问宝物的事情？\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_33,26) && !who->get_legend(TASK_33,27) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唉看来世人贪婪之性果然强于安危啊，我也不多说了，那宝物是土精和金精的守护之物，你想取得，得先取了三十个土精和三十个金精的魂魄来，我自会告诉你下一步如何做。\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_33,27) && !who->get_legend(TASK_33,28) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我看你还是打消取宝的念头吧！\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_33,28) && !who->get_legend(TASK_33,29) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来你贪婪是贪婪，不过真的有两把刷子嘛!\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_33,29) && !who->get_legend(TASK_34,1) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    恶霸朱九不知道何处习得修道之术，最近躲在虚陵洞中以那些精灵为驱，以宝物精灵珠为引修习道术，而晚上就常常来我们梦中将我们都掳到一个不知名的地方给它做人气引，而做过人气引之后那些人的身体一日不如一日，仿佛生命流失了一般，我已经被他掳去三回了，不知道如此情形继续还没有命在，你既然能够战胜为他护法的精灵，一定有办法除掉他，他就在虚陵洞的西南角。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_34,1) && !who->get_legend(TASK_34,2) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唉，下次你再来就给我收尸吧。\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_34,2) && !who->get_legend(TASK_34,3) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我们终于可以不再受他祸害了，可是这个身子，不知道如何能医治。\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_34,3) && !who->get_legend(TASK_34,4) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你干掉恶霸朱九处有注意到那旁边的宝箱吗？就在虚陵洞西南处的宝箱，那里面就有紫云洞的蕴涵了精灵之气的精灵珠，你找到之后给魏国内政官信陵君吧，他正急需这样东西，他会给你丰厚的报酬的。\n"ESC"接受任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));

	    	break;
        case 2:
        	if ( who->get_legend(TASK_33,25) && !who->get_legend(TASK_33,26) ) 
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_33,26);
			who->add_exp(70000);
			who->add_potential(880);
			who->add_cash(58000);
			send_user(who,"%c%s",';',"打探消息 经验 70000 潜能 880 金钱 58000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,37,"" );
			me->do_welcome(1);
        	}
        	break;   
	case 3:
        	if ( who->get_legend(TASK_33,26) && !who->get_legend(TASK_33,27) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_33,27);
        		who->delete_save("lidetujing");
        		who->delete_save("lidejinjing");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"魏国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,38,"证明实力" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"证明实力");
        	}
        	break;  
        case 4:
        	if ( who->get_legend(TASK_33,28) && !who->get_legend(TASK_33,29) ) 
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_33,29);
        		who->delete_save("lidetujing");
        		who->delete_save("lidejinjing");
			who->add_exp(71000);
			who->add_potential(890);
			who->add_cash(60000);
			send_user(who,"%c%s",';',"证明实力 经验 71000 潜能 890 金钱 60000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,38,"" );
			me->do_welcome(1);
        	}
        	break;
	case 5:
        	if ( who->get_legend(TASK_33,29) && !who->get_legend(TASK_34,1) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;	
        		who->set_legend(TASK_34,1);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"魏国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,39,"接受请求" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"接受请求");
        	}
        	break;  
        case 6:
        	if ( who->get_legend(TASK_34,2) && !who->get_legend(TASK_34,3) ) 
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_34,3);
			who->add_exp(72000);
			who->add_potential(900);
			who->add_cash(61000);
			send_user(who,"%c%s",';',"接受请求 经验 72000 潜能 900 金钱 61000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,39,"" );
			me->do_welcome(1);
        	}
        	break;
	case 7:
        	if ( who->get_legend(TASK_34,3) && !who->get_legend(TASK_34,4) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_34,4);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"魏国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,40,"寻宝历险" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"寻宝历险");
        	}
        	break;  
        case 8:
        	if( who->get_level() >= 25 && who->get_legend(TASK_37,21) && !who->get_legend(TASK_37,22) ) 
        		send_user(who,"%c%s",':',sprintf("%s:\n    我们一大家人也是该聚聚了，我会尽快过去的，谢谢你带来口信。\n"ESC"完成任务\ntalk %x# welcome.9\n"ESC"离开",me->get_name(),getoid(me)));
        	break;  
        case 9:
        	if ( who->get_level() >= 25 && who->get_legend(TASK_37,21) && !who->get_legend(TASK_37,22) )
		{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_37,22);
			who->add_exp(1400);
			who->add_potential(70);
			who->add_cash(1400);
			send_user(who,"%c%s",';',"家庭聚会 经验 1400 潜能 70 金钱 1400");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,65,"" );
        	}
        	break;    
        }
}