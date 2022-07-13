
// 自动生成：/make/npc/make-biao

#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

void do_task_start();
void do_task_cancel();

//void do_task_finish();
int get_char_picid() { return 0250; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Tôn Lão Đầu");
        set_city_name("Tề Quốc");

	set_2( "talk", ([
                "welcome"        : (: do_welcome :),
        ]));  
//	set("level",38);
//	set("legend",({32*10+3}));
 	set("mpLegend",([35:({32*10+3}),]));
 	set("mpLegend2",([35:({32*37+28,32*10+5,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	object me = this_object();
	string tmp="";
	
	if ( who->get("escort.finish") == 1 )
	{
		TASK_ESCORT_D->do_look_2( who, me ); 
		return ;
	}
        if(     who->get_quest("escort.flag")    // 运镖任务
        &&      who->get_quest("escort.leader") == 1    // 队长完成
        &&      who->get_quest("escort.name") == get_name() 
        && 	who->get_quest("escort.city")+" Quốc" == get_city_name() )    // 找对人了
        {
		TASK_ESCORT_D->do_look_2( who, me ); 
		return ;
	}        
	
        tmp += CHAIN_D->get_chain_menu(who,me);
	if ( ( who->get_level() >= 35 && !who->get_legend(TASK_10,3) ) || ( who->get_legend(TASK_10,3) && !who->get_legend(TASK_10,5) ) )
		tmp += sprintf(ESC HIY "索取菜种\ntalk %x# welcome.1\n",getoid(me));
	if ( who->get_level() >= 35 && who->get_legend(TASK_37,27) && !who->get_legend(TASK_37,28) )
		tmp += sprintf(ESC HIY "种庄稼的锄头\ntalk %x# welcome.4\n",getoid(me));

	send_user(who,"%c%s",':',sprintf( "%s：\n    最近这些野兔越来越猖狂，看，我在我家菜园里抓到的！我这地里的庄稼长得不怎么好呀，可能是种子不行吧，我得去找点好种子来。\n", get_name(),  ) 
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
           
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >= 35 && !who->get_legend(TASK_10,3)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    俗话说，巧妇难为无米之炊。种子不好，怎么施肥都长不出好的庄稼，我可是吃尽了这坏种子的苦头，一年辛苦到头，收成却不好，这一家几口都过着饥一顿饱一顿的日子。\n    我听说有个叫王凯的一直在研究种子，估计他那里会有好点的种子，那这里的野兔这么猖狂，我根本就脱不开身，所以你去给我找王凯要点种子来吧。\n    王凯离我这儿也不远，就在我东南方向的碣石镇。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_10,3) && !who->get_legend(TASK_10,4) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    那王凯为难你了吧？别泄气，你再去找他要，他一定会给你的！\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_10,4) && !who->get_legend(TASK_10,5) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    真是太好了，看来今年庄稼的好收成有望了，太感谢你了。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 2:
        	if ( who->get_level() >= 35 && !who->get_legend(TASK_10,3)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_10,3);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,9,"索取菜种（1）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"索取菜种（1）");
        	}
        	break;
       case 3:
        	if ( who->get_legend(TASK_10,4) && !who->get_legend(TASK_10,5) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"菜种",1) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_10,5);
			who->add_exp(3000);
			who->add_potential(70);
			who->add_cash(2000);
			send_user(who,"%c%s",';',"索取菜种（1） 经验 3000 潜能 70 金钱 2000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,9,"" );
        	}
        	break;     
        case 4:
        	if ( who->get_level() >= 35 && who->get_legend(TASK_37,27) && !who->get_legend(TASK_37,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    等了好几天，终于送过来了，快让我看看这锄头好用不好用。\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 5:
        	if ( who->get_level() >= 35 && who->get_legend(TASK_37,27) && !who->get_legend(TASK_37,28) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"种庄稼的锄头",1) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_37,28);
			who->add_exp(2500);
			who->add_potential(65);
			who->add_cash(2000);
			send_user(who,"%c%s",';',"种庄稼的锄头 经验 2500 潜能 65 金钱 2000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,72,"" );
        	}
        	break;   
        }
}