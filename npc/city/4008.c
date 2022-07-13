
// 自动生成：/make/npc/make8008

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>

#define WARDER_D        "/inh/city/warder"

inherit OFFICER;

void do_faling();
void accept_task();

// 函数：获取人物造型
int get_char_picid() { return 5102; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Ngụy Quốc Giám Ngục Quan");
        set_city_name("Ngụy Quốc");

        set_2( "talk", ([
                "faling"        : (: do_faling :),
                 "accept_task"	: (: accept_task :),
                "welcome"	: (: do_welcome :),
        ]) );
 	set("mpLegend2",([0:({32*34+18,})]));
        setup();
}

string get_master() { return CITY_WEI->get_master(); }
string get_master_2() { return CITY_WEI->get_master_2(); }
string get_master_3() { return CITY_WEI->get_master_3(); }

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( who->get_legend(TASK_34,17) && !who->get_legend(TASK_34,18) )
		tmp += sprintf(ESC HIY "官府备案\ntalk %x# welcome.1\n",getoid(me));
	if ( who->get_legend(TASK_34,18) && !who->get_legend(TASK_34,19) )
		tmp += sprintf(ESC HIY "奏请王命\ntalk %x# welcome.1\n",getoid(me));

	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		WARDER_D->do_look( who, this_object() ); 
	
}

void do_faling() { WARDER_D->do_faling( this_player(), this_object() ); }

void accept_task() { WARDER_D->accept_task( this_player(), this_object() );}


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
        	if ( who->get_legend(TASK_34,17) && !who->get_legend(TASK_34,18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    嗯，这种骗子是该杀。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_34,18) && !who->get_legend(TASK_34,19) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    啊，魏老汉的事情我已经听说了，现在这些神棍实在太可恶了，骗人钱财，扰乱治安，本官起草了一份请奏书，你代我转呈大王，必定要让这些装神弄鬼之人无立锥之地。\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break; 
	case 2:
        	if ( who->get_legend(TASK_34,17) && !who->get_legend(TASK_34,18) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_34,18);
			who->add_exp(73000);
			who->add_potential(910);
			who->add_cash(63000);
			send_user(who,"%c%s",';',"官府备案 经验 73000 潜能 910 金钱 63000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,45,"" );
  			me->do_welcome(1);
	      	}
        	break; 
        case 3:
        	if ( who->get_legend(TASK_34,18) && !who->get_legend(TASK_34,19) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
			TASK_LEGEND_D->give_item(who,"item/98/0160",1);
        		who->set_legend(TASK_34,19);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,46,"奏请王命" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"奏请王命");
        	}
        	break;
        case 99:
        	WARDER_D->do_look( who, me ); 
        	break;
        }
}