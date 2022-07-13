
// 自动生成：/make/npc/make-collect

#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <task.h>
#include <music.h>

inherit OFFICER;

void do_welcome(string arg);

// 函数：获取人物造型
int get_char_picid() { return 5401; }

// 函数：构造处理
void create()
{
        set_name("Dược Tài Thương");

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));      
//        set("level",45);
//        set("legend",({32*11+27}));
	set("mpLegend",([45:({32*11+27}),]));
	set("mpLegend2",([45:({32*11+29}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
        tmp += CHAIN_D->get_chain_menu(who,this_object());
        if ( (who->get_level() >= 45 && !who->get_legend(TASK_11,27)) || (who->get_legend(TASK_11,27)&&!who->get_legend(TASK_11,29)) ) 
		tmp += sprintf(ESC HIY "研究石元素\ntalk %x# welcome.1\n",getoid(this_object())); 

        send_user( who, "%c%s", ':', sprintf( "%s：\n    光靠贩卖药材可能赚不了钱，我得想点别的办法。\n", get_name())
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
        	if ( who->get_level() >= 45 && !who->get_legend(TASK_11,27) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我需要一些会发光的石头，我想研究他们发光的原因，可能这是一味好的药材。你去给我找5块来吧。在长白天池的魍魉身上或许能找到。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_11,27) && !who->get_legend(TASK_11,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果实在找不到，那我也没办法了，不过还是希望你能尽力！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_11,28)&&!who->get_legend(TASK_11,29) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    等我研究成功，我一定会无偿送你这些药材的，到时候你也可以拿去卖，赚点小钱。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
 	      	break;
     
        case 2:
        	if( who->get_level() >= 45 && !who->get_legend(TASK_11,27) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_11,27);
        		who->delete_save_2("yanjiushitou");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"燕国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,19,"研究石头" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"研究石头");
        	}
        	break;

        case 3:
        	if( who->get_legend(TASK_11,28) && !who->get_legend(TASK_11,29) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"发光的石头",5) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_11,29);
        		who->delete_save_2("yanjiushitou");
			who->add_exp(5000);
			who->add_potential(160);
			who->add_cash(4000);
			send_user(who,"%c%s",';',"研究石头 经验 5000 潜能 160 金钱 4000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,19,"" );
        	}
        	break;
        }
}