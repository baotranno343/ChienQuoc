
// 自动生成：/make/npc/make-collect

#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <task.h>
#include <music.h>

inherit OFFICER;
void do_welcome(string arg);


// 函数：获取人物造型
int get_char_picid() { return 5909; }

// 函数：构造处理
void create()
{
        set_name("Kì Đồng Tiểu Hắc");

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));      
//        set("level",39);
//        set("legend",({32*10+8}));
 	set("mpLegend",([35:({32*10+8}),]));
 	set("mpLegend2",([35:({32*10+10}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
        tmp += CHAIN_D->get_chain_menu(who,this_object());
        if ( (who->get_level() >= 35 && !who->get_legend(TASK_10,8)) || (who->get_legend(TASK_10,8)&&!who->get_legend(TASK_10,10)) ) 
		tmp += sprintf(ESC HIY "丢失的黑棋子\ntalk %x# welcome.1\n",getoid(this_object())); 
        send_user( who, "%c%s", ':', sprintf( "%s：\n    %s\n", get_name(),TASK_COLLECT_D->get_talk_string(0701))
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
        	if (who->get_level() >= 35 && !who->get_legend(TASK_10,8))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我刚来太公府做棋童没几天，就弄丢了几颗棋子，虽然老爷夫人没有责怪我，可我老觉得内疚，想要弥补自己的过错。\n    听说泰山的黑熊那有棋子，我想去找3颗来，可那泰山实在太险恶，我一个小孩子，不敢只身前往，哥哥/姐姐，我看你一身武艺了得，能不能帮帮我，去给我找3颗棋子来呢？\n    从我这太公府出去，就能直接到泰山了。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_10,8) && !who->get_legend(TASK_10,9) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唉，虽然老爷和夫人不会责怪我，但是我还是想弥补自己的过错，你能再跑一趟吗？\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_10,9) && !who->get_legend(TASK_10,10) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    谢谢%s，这下老爷和夫人肯定会夸我的，呵呵，真开心。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),NPC_RANK_D->get_respect_2(who),getoid(me)));
        	break;
        case 2:
        	if(who->get_level() >= 35 && !who->get_legend(TASK_10,8))
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_10,8);
        		who->delete_save_2("qtheiqizi");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"齐国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,11,"丢失的黑棋子" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"丢失的黑棋子");
        	}
        	break;
       case 3:
        	if ( who->get_legend(TASK_10,9) && !who->get_legend(TASK_10,10) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"黑棋子",1) != 1 )
        			return;
        		who->delete_save_2("qtheiqizi");
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_10,10);
			who->add_exp(4000);
			who->add_potential(115);
			who->add_cash(3000);
			send_user(who,"%c%s",';',"丢失的黑棋子 经验 4000 潜能 115 金钱 3000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,11,"" );
        	}
        	break;        
        }
}