
// 自动生成：/make/npc/make-collect

#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <task.h>
#include <music.h>

inherit OFFICER;

void do_task();

// 函数：获取人物造型
int get_char_picid() { return 5301; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Thôi Đại Quan");

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));      
	set("mpLegend2",([0:({32*7+29,}),20:({32*37+20,}),95:({32*38+20,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
        tmp += CHAIN_D->get_chain_menu(who,this_object());
        if ( who->get_legend(TASK_07,28) && !who->get_legend(TASK_07,29) ) 
		tmp += sprintf(ESC HIY "唤醒记忆\ntalk %x# welcome.1\n",getoid(this_object())); 
        if ( who->get_level() >= 20 && who->get_legend(TASK_37,19) && !who->get_legend(TASK_37,20) ) 
		tmp += sprintf(ESC HIY "请柬\ntalk %x# welcome.3\n",getoid(this_object())); 
        if ( who->get_level() >= 95 && who->get_legend(TASK_38,19) && !who->get_legend(TASK_38,20) ) 
		tmp += sprintf(ESC HIY "遗忘的佩剑\ntalk %x# welcome.5\n",getoid(this_object())); 

        send_user( who, "%c%s", ':', sprintf( "%s：\n    我是谁，我不记得了，我要干嘛，我也不记得了，怎么办？怎么办？\n", get_name())
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
        	if ( who->get_legend(TASK_07,28) && !who->get_legend(TASK_07,29) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    原来三年前的马失足才造成了我失去记忆，可怜我命苦的老婆孩子都不幸丧命！不管怎样，我都要坚强得活下去！你是我的有缘人，我要好好感谢你！\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 2:
        	if ( who->get_legend(TASK_07,28) && !who->get_legend(TASK_07,29) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"羽毛",1) != 1 )
        			return;
        		TASK_LEGEND_D->give_item(who,"item/product/63006",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_07,29);
			who->add_exp(4000);
			who->add_potential(50);
			who->add_cash(2800);
			send_user(who,"%c%s",';',"唤醒记忆 经验 4000 潜能 50 金钱 2800 鹤顶红图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,12,"" );
        	}
        	break;
        case 3:
        	if( who->get_level() >= 20 && who->get_legend(TASK_37,19) && !who->get_legend(TASK_37,20) ) 
        		send_user(who,"%c%s",':',sprintf("%s:\n    请柬我收下了，至于要不要去韩国军营，还容我考虑一下，我会自己向韩国大将军回复的，谢谢你送来这封请柬。\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开",me->get_name(),getoid(me)));
        	break;  
        case 4:
        	if ( who->get_level() >= 20 && who->get_legend(TASK_37,19) && !who->get_legend(TASK_37,20) ) 
		{
        		if (TASK_LEGEND_D->check_task_item(who,"请柬",1) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_37,20);
			who->add_exp(1200);
			who->add_potential(60);
			who->add_cash(1200);
			send_user(who,"%c%s",';',"崔大官人的请柬 经验 1200 潜能 60 金钱 1200");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,48,"" );
        	}
        	break;    
        case 5:
        	if( who->get_level() >= 95 && who->get_legend(TASK_38,19) && !who->get_legend(TASK_38,20) ) 
        		send_user(who,"%c%s",':',sprintf("%s:\n    你来得真凑巧，我刚刚叫人把佩剑给他送回去！\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开",me->get_name(),getoid(me)));
        	break;  
        case 6:
        	if ( who->get_level() >= 95 && who->get_legend(TASK_38,19) && !who->get_legend(TASK_38,20) ) 
		{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_38,20);
			who->add_exp(35000);
			who->add_potential(600);
			who->add_cash(30000);
			send_user(who,"%c%s",';',"遗忘的佩剑 经验 35000 潜能 600 金钱 30000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,45,"" );
        	}
        	break;    
        }

}
