
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
        set_name("Lê Lão Hán");

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));      
//        set("level",32);
//        set("legend",({32*8+13}));
	set("mpLegend",([30:({32*8+13})]));
	set("mpLegend2",([30:({32*8+15,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
        tmp += CHAIN_D->get_chain_menu(who,this_object());
        if ( (who->get_level() >= 30 && !who->get_legend(TASK_08,13)) || (who->get_legend(TASK_08,13)&&!who->get_legend(TASK_08,15)) ) 
		tmp += sprintf(ESC HIY "湖泊奇闻\ntalk %x# welcome.1\n",getoid(this_object())); 
        send_user( who, "%c%s", ':', sprintf( "%s：\n    %s\n", get_name(),TASK_COLLECT_D->get_talk_string(0111))
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
        	if ( who->get_level() >= 30 && !who->get_legend(TASK_08,13) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我们这村子里最近老有人失踪，这些失踪的人都有一个共同特征，临失踪前都去过鄱阳湖，我很小的时候听老人们说过，在很多年前，鄱阳湖里有一只水湖怪，经常出来害人，被道士们封在湖底两百年，两百年过去了，封印解除了，所以我估计那些失踪的人口都与这只水湖怪有关，我年纪大了，做不了这件事了，所以请你前去鄱阳湖的鄱阳码头将那水湖怪铲除掉，然后回来告诉我一声，也好让村子里的人安心。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_08,13) && !who->get_legend(TASK_08,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来那水湖怪确实厉害，我得赶快通知我那些老朋友尽快搬家。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_08,14) && !who->get_legend(TASK_08,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下可好了，我那些老朋友不用搬家了。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 2:
        	if ( who->get_level() >= 30 && !who->get_legend(TASK_08,13) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_08,13);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"楚国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,17,"湖泊奇闻" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"湖泊奇闻");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_08,14) && !who->get_legend(TASK_08,15) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/63007",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_08,15);
			who->add_exp(2500);
			who->add_potential(90);
			who->add_cash(1800);
			send_user(who,"%c%s",';',"湖泊奇闻 经验 2500 潜能 90 金钱 1800 玉容膏图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,17,"" );
        	}
        	break;   
   
        }
}