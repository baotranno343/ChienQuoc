
// 自动生成：/make/npc/make0007

#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>

inherit OFFICER;

// 函数：修理师傅
int is_repairer() { return 1; }
void do_welcome( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5407; }

// 函数：构造处理
void create()
{
        set_name("Chủ Tiệm Sửa Chữa");
	set_real_name("Phiền Vu Kì");
        set_city_name("Yên Quốc");
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
//	set("level",48);
//	set("legend",({32*12+19}));
	set("mpLegend",([45:({32*12+19}),]));
	set("mpLegend2",([45:({32*12+21}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp;
	"/quest/help"->send_help_tips(who, 52);
	if ( (who->get_level() >= 45 &&!who->get_legend(TASK_12, 19)) || (who->get_legend(TASK_12, 19)&&!who->get_legend(TASK_12, 21)) )
	{
		tmp = get_name() + "：\n    "+"/quest/word"->get_normal_word(this_object()) + "\n"+
			sprintf("\n"ESC"修理和鉴定\ntalk %x# welcome.99\n",getoid(this_object()))+
               		sprintf(ESC HIY "郑国渠里的哭声\ntalk %x# welcome.1\n",getoid(this_object())) ;	
	}
	if ( stringp(tmp) )
	{
		tmp += ESC"离开";
		send_user( who, "%c%s", ':',tmp);
	}	
	else	
        	REPAIR_CMD->main( who, sprintf( "%x#", getoid( this_object() ) ) );
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
	       	if ( who->get_level() >= 45 && !who->get_legend(TASK_12,19) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我昨天经过郑国渠的时候，隐约听到有女子的哭声。当时天色较晚，我不敢逗留。不知你是否愿意前去打探一下?\n    如果你查出了什么，一定要及时向我汇报，如果是有妖怪害人，那么你就直接干掉他吧！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_12,19) && !who->get_legend(TASK_12,20) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    太可怕了，我以后再也不从那里路过了。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_12,20) && !who->get_legend(TASK_12,21) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下可好了，那里可以安静一段时间了。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        		
        	break;
	case 2:
        	if( who->get_level() >=45 && !who->get_legend(TASK_12,19) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_12,19);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,7,"郑国渠里的哭声" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"郑国渠里的哭声");
        	}
        	break;       
        case 3:
        	if ( who->get_legend(TASK_12,20) && !who->get_legend(TASK_12,21) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_12,21);
			who->add_exp(5200);
			who->add_potential(190);
			who->add_cash(4600);
			send_user(who,"%c%s",';',"郑国渠里的哭声 经验 5200 潜能 190 金钱 4600");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,7,"" );
        	}
        	break;   
        case 99:
		REPAIR_CMD->main( who, sprintf( "%x#", getoid( me ) ) );
        	break;
        }
}