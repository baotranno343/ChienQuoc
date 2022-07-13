
// 自动生成：/make/npc/make8020

#include <npc.h>
#include <ansi.h>
#include <task.h>

#define INTERIOR_D      "/inh/city/interior"

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 0452; }
void do_welcome(string arg);

// 函数：师父识别
int is_master() { return 1; }

// 函数：师父识别(武教头)
int is_basic_master() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Yên Quốc Công Tượng");
        set_city_name("Yên Quốc");
        set_2( "talk", ([
                "welcome"	: (: do_welcome :),
        ]) );
//        set("level",46);
//        set("legend",({32*12+4}));
	set("mpLegend",([45:({32*12+4}),]));
	set("mpLegend2",([45:({32*12+6}),]));
        set_skill(0670, 80);
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
	object me = this_object();
	if ( ( who->get_level() >= 45 && !who->get_legend(TASK_12,4) ) || ( who->get_legend(TASK_12,4) && !who->get_legend(TASK_12,6) ) )
	{
		tmp = sprintf(ESC HIY "忍气吞声\ntalk %x# welcome.1\n",getoid(me));
	}
	tmp += sprintf(ESC"学习生活技能\nlearn ? %s\n", me->get_char_id());
	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) ,get_name()));
	
}

int accept_object( object who, object obj ) { return INTERIOR_D->accept_object_2( who, this_object(), obj, 8 ); }
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
        	if ( who->get_level() >=45 && !who->get_legend(TASK_12,4) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我卖命为国家修筑工事，那工头胡山还经常打骂我，故意找茬克扣我的工钱。你愿意帮我讨回公道吗？\n    那恶工头胡山就在郑国渠，你赶快去吧！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_12,4) && !who->get_legend(TASK_12,5) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    算了，我还是忍气吞声吧！免得又被他报复。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_12,5) && !who->get_legend(TASK_12,6) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    总算有出头之日了。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 2:
        	if( who->get_level() >=45 && !who->get_legend(TASK_12,4) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_12,4);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,2,"忍气吞声" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"忍气吞声");
        	}
        	break;       
        case 3:
        	if ( who->get_legend(TASK_12,5) && !who->get_legend(TASK_12,6) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/61008",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_12,6);
			who->add_exp(4600);
			who->add_potential(170);
			who->add_cash(3900);
			send_user(who,"%c%s",';',"忍气吞声 经验 4600 潜能 170 金钱 3900 鸡蛋汤图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,2,"" );
        	}
        	break;   
        }
}