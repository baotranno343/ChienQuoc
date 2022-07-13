
// 自动生成：/make/npc/make8014

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>

#define GUARDER_D       "/inh/city/guarder"

inherit OFFICER;

void do_enter();
void do_record();

// 函数：获取人物造型
int get_char_picid() { return 0050; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Sở Quốc Thủ Vệ");
        set_city_name("Sở Quốc");

        set_2( "talk", ([
                "enter"         : (: do_enter :),
                "record"	: (: do_record :),
                "welcome"	: (: do_welcome :),
        ]) );
        set("out", 10);
        set("in", 12);
//        set("level",34);
//        set("legend",({32*9+4}));
 	set("mpLegend",([30:({32*9+4}),90:({32*38+19})]));
 	set("mpLegend2",([30:({32*9+6}),]));
        setup();
}

string get_master() { return CITY_CHU->get_master(); }
string get_master_2() { return CITY_CHU->get_master_2(); }
string get_master_3() { return CITY_CHU->get_master_3(); }

void do_look( object who )
{ 
	string tmp="";
	object me = this_object();
	if ( (who->get_level() >= 30 && !who->get_legend(TASK_09,4)) || (who->get_legend(TASK_09,4)&&!who->get_legend(TASK_09,6)) )
	{
		tmp = sprintf(ESC HIY "湖口村的悬案\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( who->get_level() >= 90 && !who->get_legend(TASK_38,19) )
		tmp += sprintf(ESC HIY "遗忘的佩剑\ntalk %x# welcome.4\n",getoid(me));


	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		GUARDER_D->do_look( who, me ); 
	
}
void do_enter() { GUARDER_D->do_enter( this_player(), this_object() ); }

void do_record() { GUARDER_D->do_record( this_player(), this_object() ); }
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
        	if ( who->get_level() >= 30 && !who->get_legend(TASK_09,4) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我身为楚国的守卫，不仅肩负着保护楚城安全的使命，还与我的兄弟们一起保护楚国百姓韩让的安全。\n    最近接到百姓的报案，在鄱阳湖的湖口村一带经常有小孩子失踪，根据留下来的线索发现，极有可能是赵小三这个人贩子做的，他经常拐卖小孩给外地那些没有生育的人，以换取好价钱来供自己吃喝嫖赌。\n    我现在在站岗，脱不开身，而此事不容迟，你前去鄱阳湖的湖口村帮我调查下吧。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_09,4) && !who->get_legend(TASK_09,5) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这事不简单啊！看来我得找个时间亲自去一趟。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_09,5) && !who->get_legend(TASK_09,6) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    谢谢你啊！你真是帮了我一个大忙，我一定会报答你。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 2:
        	if ( who->get_level() >= 30 && !who->get_legend(TASK_09,4) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_09,4);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,24,"湖口村的悬案" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"湖口村的悬案");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_09,5) && !who->get_legend(TASK_09,6) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_09,6);
			who->add_exp(2600);
			who->add_potential(100);
			who->add_cash(2000);
			send_user(who,"%c%s",';',"湖口村的悬案 经验 2600 潜能 100 金钱 2000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,24,"" );
        	}
        	break;   
	case 4:
		if ( who->get_level() >= 90 && !who->get_legend(TASK_38,19) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    崔大官人是我的表叔呢！\n    前些日子去他家作客，他可是热情款待啊，我当时喝了不少酒，居然把佩剑落在他家了，我当时还没想起来，回到家后找了很久没找到，仔细一思量，估计是落在他家了，你去替我瞧瞧，看有没有在他家？有的话你给我拿回来。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
		break;
	case 5:
        	if ( who->get_level() >= 90 && !who->get_legend(TASK_38,19) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_38,19);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,45,"遗忘的佩剑" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"遗忘的佩剑");
        	}
        	break;
	case 99:
        	GUARDER_D->do_look( who, me ); 
        	break;     
        }
}