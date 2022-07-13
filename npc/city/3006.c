
// 自动生成：/make/npc/make8006

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>

#define INQUISITOR_D    "/inh/city/inquisitor"

inherit OFFICER;

void do_elect( string arg );
void do_vote( string arg );
void do_score( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5102; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Triệu Quốc Ngự Sử");
	set_real_name("Mạc Thiên Hành");
        set_city_name("Triệu Quốc");

        set_2( "talk", ([
                "elect"         : (: do_elect :),
                "vote"          : (: do_vote :),
                "score"         : (: do_score :),
                "welcome"	: (: do_welcome :),
        ]) );
//        set("level",108);
//        set("legend",({32*42+10}));
 	set("mpLegend",([105:({32*42+10})]));
 	set("mpLegend2",([0:({32*42+30})]));
        setup();
}

string get_master() { return CITY_ZHAO->get_master(); }
string get_master_2() { return CITY_ZHAO->get_master_2(); }
string get_master_3() { return CITY_ZHAO->get_master_3(); }

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( who->get_level() >= 105 && !who->get_legend(TASK_42,10) )
		tmp += sprintf(ESC HIY "询查原因\ntalk %x# welcome.1\n",getoid(me));
	if ( who->get_legend(TASK_42,29) && !who->get_legend(TASK_42,30) )
		tmp += sprintf(ESC HIY "枉法之徒\ntalk %x# welcome.3\n",getoid(me));
	if ( who->get_legend(TASK_42,30) && !who->get_legend(TASK_43,3) )
		tmp += sprintf(ESC HIY "施行仁政\ntalk %x# welcome.3\n",getoid(me));

	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		INQUISITOR_D->do_look( who, this_object() ); 
	
}
void do_elect( string arg ) { INQUISITOR_D->do_elect( this_player(), this_object(), arg ); }
void do_vote( string arg ) { INQUISITOR_D->do_vote( this_player(), this_object(), arg ); }
void do_score( string arg ) { INQUISITOR_D->do_score( this_player(), this_object(), arg ); }

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
        	if ( who->get_level() >= 105 && !who->get_legend(TASK_42,10) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我国探子报告最近发现一伙来路不明、鬼鬼祟祟的人聚集在城外附近，隐隐约约听得什么刺杀、将军、赏赐什么的，我命你速速前往市井向百姓打听一下，看有否人知道更详尽的消息。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
	case 2:
        	if ( who->get_level() >= 105 && !who->get_legend(TASK_42,10) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_42,10);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,78,"询查原因" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"询查原因");
        	}
        	break; 
        case 3:
        	if ( who->get_legend(TASK_42,29) && !who->get_legend(TASK_42,30) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    枉法之人终于伏法，看来这次事件也值得我们深思啊。\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_42,30) && !who->get_legend(TASK_43,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    此番民情探察暴露了我国政法体制的诸多问题，值得深思啊，我写了一封奏章，关于本国律法及其实施的问题，你代我交给大王，希望大王多施仁政，以得民心。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
 	case 4:
		if ( who->get_legend(TASK_42,29) && !who->get_legend(TASK_42,30) )
		{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_42,30);
			who->add_exp(100000);
			who->add_potential(1950);
			who->add_cash(90000);
			send_user(who,"%c%s",';',"枉法之徒 经验 100000 潜能 1950 金钱 90000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,86,"" );
			me->do_welcome(3);
        	} 
		break;
	case 5:
		if ( who->get_legend(TASK_42,30) && !who->get_legend(TASK_43,3) )
		{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
        		TASK_LEGEND_D->give_item(who,"item/98/0208",1);  
        		who->set_legend(TASK_43,3);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,87,"施行仁政" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"施行仁政");
        	}
		break;
        case 99:	
		INQUISITOR_D->do_look( who, me); 
        	break;
        }
}      