
// 自动生成：/make/npc/make8007

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>

#define DIPLOMAT_D      "/inh/city/diplomat"

inherit OFFICER;

void do_relation( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5102; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Triệu Quốc Sử Tiết");
	set_real_name("Mao Toại");
        set_city_name("Triệu Quốc");

        set_2( "talk", ([
                "relation"      : (: do_relation :),
                "welcome"	: (: do_welcome :),
        ]) );
//	set("level",55);
//	set("legend",({32*16+6}));
	set("mpLegend",([55:({32*16+6}),110:({32*43+5})]));
 	set("mpLegend2",([0:({32*21+21})]));	
        setup();
}

string get_master() { return CITY_ZHAO->get_master(); }
string get_master_2() { return CITY_ZHAO->get_master_2(); }
string get_master_3() { return CITY_ZHAO->get_master_3(); }

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( ( who->get_level() >= 55 && !who->get_legend(TASK_16,6) ) || ( who->get_legend(TASK_16,6) && !who->get_legend(TASK_16,7) ) )
	{
		tmp = sprintf(ESC HIY "出使秦国\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( who->get_legend(TASK_21,20) && !who->get_legend(TASK_21,21) )
	{
		tmp += sprintf(ESC HIY "出使信函\ntalk %x# welcome.3\n",getoid(me));
	}
	if ( who->get_legend(TASK_21,21) && !who->get_legend(TASK_21,22) )
	{
		tmp += sprintf(ESC HIY "面见赵王迁\ntalk %x# welcome.3\n",getoid(me));
	}
	if ( who->get_level() >= 110 && !who->get_legend(TASK_43,5) )
		tmp = sprintf(ESC HIY "询察起因\ntalk %x# welcome.6\n",getoid(me));
	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		DIPLOMAT_D->do_look( who, this_object() ); 
	
}

void do_relation( string arg ) { DIPLOMAT_D->do_relation( this_player(), this_object(), arg ); }

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
        	if ( who->get_level() >= 55 && !who->get_legend(TASK_16,6) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    有了上次成功的出使秦国，大王对我更放心了，这次又派我出使秦国，并且还说我可以带助手，你愿意和我一起出使秦国吗？如果愿意的话，你可以先行一步拜访秦国使节，我随后就到。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_16,6) && !who->get_legend(TASK_16,7) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你可以先行到秦国，无须等我。\n"ESC"离开", me->get_name(),NPC_RANK_D->get_respect_2(who)));
        	break;
	case 2:
        	if( who->get_level() >= 55 && !who->get_legend(TASK_16,6) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_16,6);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,8,"出使秦国" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"出使秦国");
        	}
        	break;   
        case 3:
        	if ( who->get_legend(TASK_21,20) && !who->get_legend(TASK_21,21) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    信函我已收到，看来我们鸟夷人是该修好方不为外族所乘，我会在朝堂之上隐讳的向我王吹吹风，成与不成却只有看天意了。\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_21,21) && !who->get_legend(TASK_21,22) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    今日朝堂之上我已经向大王提起了秦赵相亲的好处，同时内政官大人也向大王通报了秦国使节在路上的消息，但是君威难测，至于如何决断，你最好亲自面见大王才能问个清楚。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
	case 4:
        	if ( who->get_legend(TASK_21,20) && !who->get_legend(TASK_21,21) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"出使信函",1) != 1 )
        			return;        		
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_21,21);
			who->add_exp(17000);
			who->add_potential(390);
			who->add_cash(17000);
			send_user(who,"%c%s",';',"出使信函 经验 17000 潜能 390 金钱 17000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,35,"" );
			me->do_welcome(3);
        	}
        	break;
	case 5:
        	if ( who->get_legend(TASK_21,21) && !who->get_legend(TASK_21,22) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_21,22);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QINGUO,"Tần Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,36,"面见赵王" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"面见赵王");
        	}
        	break;        	
	case 6:
		if ( who->get_level() >= 110 && !who->get_legend(TASK_43,5) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我在出使的路过邯郸城郊时，时常听得人们议论纷纷，说得是那里经常发生人口失踪之事，我对此甚为忧心，但是职责所系，不能多做停留，你去向本国百姓细细探察一下此事原委。\n"ESC"接受任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
		break;
	case 7:
		if ( who->get_level() >= 110 && !who->get_legend(TASK_43,5) )
		{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_43,5);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,88,"询察起因" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"询察起因");
        	}	
		break;
        case 99:	
		DIPLOMAT_D->do_look( who, me); 
        	break;
        }
}