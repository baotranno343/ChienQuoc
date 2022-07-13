
// 自动生成：/make/npc/make-collect

#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <task.h>
#include <music.h>

inherit OFFICER;

void do_welcome(string arg);

// 函数：获取人物造型
int get_char_picid() { return 5801; }

// 函数：构造处理
void create()
{
        set_name("Yên Lão Hán");

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),

        ]));      
//        set("level",51);
//        set("legend",({32*14+1}));
	set("mpLegend",([50:({32*14+1}),]));
	set("mpLegend2",([50:({32*14+3}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
        tmp += CHAIN_D->get_chain_menu(who,this_object());
        if ( (who->get_level() >= 50 && !who->get_legend(TASK_14,1)) || (who->get_legend(TASK_14,1)&&!who->get_legend(TASK_14,3)) ) 
		tmp += sprintf(ESC HIY "报仇雪恨\ntalk %x# welcome.1\n",getoid(this_object())); 
 
        send_user( who, "%c%s", ':', sprintf( "%s：\n    %s\n", get_name(),TASK_COLLECT_D->get_talk_string(0721))
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
	       	if ( who->get_level() >= 50 && !who->get_legend(TASK_14,1) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呜呜呜……可怜我白发人送黑发人啊～\n    去年年关，我的儿子赶回家过年，从燕长城经过时，被10个剑盾兵围攻杀死了！！！真是一群令人发指的恶魔，我一定要想尽千方百计除掉他们，为我儿子报仇！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_14,1) && !who->get_legend(TASK_14,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果我儿的仇报不了，就算是死，我也不会瞑目的。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_14,2) && !who->get_legend(TASK_14,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    儿子的仇报了，就算是死，我也瞑目了。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        		
        	break;
	case 2:
        	if( who->get_level() >=50 && !who->get_legend(TASK_14,1) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_14,1);
        		who->delete_save_2("bcjdbing");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"燕国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,23,"报仇雪恨" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"报仇雪恨");
        	}
        	break;       
        case 3:
        	if ( who->get_legend(TASK_14,2) && !who->get_legend(TASK_14,3) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_14,3);
        		who->delete_save_2("bcjdbing");
			who->add_exp(5800);
			who->add_potential(230);
			who->add_cash(4700);
			send_user(who,"%c%s",';',"报仇雪恨 经验 5800 潜能 230 金钱 4700");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,23,"" );
        	}
        	break;   
		
        }
}