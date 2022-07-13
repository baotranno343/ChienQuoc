
// 自动生成：/make/npc/make8010

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>
#define GUARDER_D       "/inh/city/guarder"

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 0050; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Sở Quốc Thủ Vệ");
        set_city_name("Sở Quốc");
        set_2( "talk", ([
                "welcome"	: (: do_welcome :),
        ]) );
//        set("level",95);
//        set("legend",({32*33+13}));
 	set("mpLegend",([95:({32*33+13}),]));
 	set("mpLegend2",([95:({32*33+15}),]));
        setup();
}

string get_master() { return CITY_CHU->get_master(); }
string get_master_2() { return CITY_CHU->get_master_2(); }
string get_master_3() { return CITY_CHU->get_master_3(); }

void do_look( object who )
{ 
	int id;
	string tmp="";
	object me = this_object();
	id = getoid(me);
	if ( ( who->get_level() >= 95 && !who->get_legend(TASK_33,13) ) || ( who->get_legend(TASK_33,13) && !who->get_legend(TASK_33,15) ) )
		tmp += sprintf(ESC HIY "玫瑰花\ntalk %x# welcome.1\n",id);

	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		GUARDER_D->do_look_3( who, me ); 
	
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
		if ( who->get_level() >= 95 && !who->get_legend(TASK_33,13) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唉，最近我每天晚上都睡不着觉，每天来站岗都是黑眼圈，谁可以救救我啊？呃你问我什么事情？说起来真不好意思，我最近暗恋上了一个人，可是一直没有勇气去表白，听说玫瑰花代表爱情，我想给心上人送11朵玫瑰花，可惜城门官硬是不准假，没有时间去虚陵洞找，你能帮我找来吗？\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_33,13) && !who->get_legend(TASK_33,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    没有玫瑰花，我要怎样表达我的心意呢？\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_33,14) && !who->get_legend(TASK_33,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    谢谢你，亲爱的%s，我这个玫瑰花就是送给你的啊，你现在明白我的心意了吗？\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),who->get_name(),getoid(me)));
		break;
        case 2:
        	if ( who->get_level() >= 95 && !who->get_legend(TASK_33,13) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_33,13);
        		who->delete_save("cgswmeigui");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,37,"玫瑰花" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"玫瑰花");        		
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_33,14) && !who->get_legend(TASK_33,15) )
        	{
			if ( TASK_LEGEND_D->check_task_item(who,"玫瑰花",11) != 1)
				return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_33,15);
        		who->delete_save("cgswmeigui");
			who->add_exp(63500);
			who->add_potential(910);
			who->add_cash(55000);
			send_user(who,"%c%s",';',"玫瑰花 经验 63500 潜能 910 金钱 55000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,37,"" );
        	}
        	break;

        case 99:
        	GUARDER_D->do_look_3( who, me ); 
        	break;
        }
}