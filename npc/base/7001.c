
// 自动生成：/make/npc/make0001

#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>

inherit OFFICER;

// 函数：Quản Khố
int is_banker() { return 1; }

// 函数：获取人物造型
int get_char_picid() { return 5301; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Quản Khố");
        set_real_name("Quản Khố");
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
//	set("level",49);
//	set("legend",({32*13+7})); 
	set("mpLegend",([50:({32*13+7}),]));
	set("mpLegend2",([50:({32*13+9}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
	
	if ( ( who->get_level() >= 50 && !who->get_legend(TASK_13,7) ) || ( who->get_legend(TASK_13,7) && !who->get_legend(TASK_13,9) ) )
		tmp =  sprintf(ESC HIY "可怕的预言\ntalk %x# welcome.1\n",getoid(this_object()));
	
        send_user( who, "%c%c%w%s", ':', 1, get_char_picid(), 
                sprintf("%s：\n    "+"/quest/word"->get_normal_word(this_object())+"\n"
                        ESC "我想使用当铺\npawn %x# 1\n"
                        ESC "我要扩充我的当铺\npawn expand %x# 0\n"
                        + tmp +
                        ESC "我只是随便看看\nCLOSE\n", who->get_name(), getoid(this_object()), getoid(this_object()) ) );
	"/quest/help"->send_help_tips(who, 4);                        
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
        	if ( who->get_level() >= 50 && !who->get_legend(TASK_13,7) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    听风水先生预言，不久后在郑国渠一带将有妖孽横空出世，这妖孽不知道会做出什么危害人间的事情，所以应该防范于未然，阻止他的出世，如果我没猜错的话，应该是逆世鬼在作祟，你是否愿意前去将此事调查清楚？\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_13,7) && !who->get_legend(TASK_13,8) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这段时间我是不会从郑国渠那里经过，以防万一。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_13,8) && !who->get_legend(TASK_13,9) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下再也不用担心那预言是真是假，可以安静的过日子了。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        		
        	break;
	case 2:
        	if( who->get_level() >=50 && !who->get_legend(TASK_13,7) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_13,7);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,13,"可怕的预言" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"可怕的预言");
        	}
        	break;       
        case 3:
        	if ( who->get_legend(TASK_13,8) && !who->get_legend(TASK_13,9) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/64074",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_13,9);
			who->add_exp(5600);
			who->add_potential(220);
			who->add_cash(4800);
			send_user(who,"%c%s",';',"可怕的预言 经验 5600 潜能 220 金钱 4800 踏云甲图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,13,"" );
        	}
        	break; 
  
        }
}