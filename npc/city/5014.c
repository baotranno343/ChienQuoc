
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
int get_char_picid() { return 0651; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Tần Quốc Thủ Vệ");
        set_city_name("Tần Quốc");

        set_2( "talk", ([
                "enter"         : (: do_enter :),
                "record"	: (: do_record :),
                "welcome"	: (: do_welcome :),
        ]) );
        set("out", 11);
        set("in", 13);
	set("mpLegend",([80:({32*38+13})]));
	set("mpLegend2",([100:({32*38+26}),110:({32*38+30}),]));
        setup();
}

string get_master() { return CITY_QIN->get_master(); }
string get_master_2() { return CITY_QIN->get_master_2(); }
string get_master_3() { return CITY_QIN->get_master_3(); }

void do_look( object who )
{ 
	string tmp="";
	object me = this_object();

	if ( who->get_level() >= 80 && !who->get_legend(TASK_38,13) )
		tmp += sprintf(ESC HIY "身世之谜\ntalk %x# welcome.1\n",getoid(me));
	if ( who->get_level() >= 100 && who->get_legend(TASK_38,25) && !who->get_legend(TASK_38,26) )
		tmp += sprintf(ESC HIY "挑战\ntalk %x# welcome.3\n",getoid(me));
	if ( who->get_level() >= 110 && who->get_legend(TASK_38,29) && !who->get_legend(TASK_38,30) )
		tmp += sprintf(ESC HIY "挖掘人才\ntalk %x# welcome.5\n",getoid(me));

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
        	if ( who->get_level() >= 80 && !who->get_legend(TASK_38,13) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我是个孤儿。\n    从我记事的那天起，我就没见过我的爹娘，现在我长大了，我特别想找到自己的亲生父母，经过我的努力与多方打听，终于让我知道，赵总管这个人极有可能知道我的身世，我自己非常想去问个清楚，可是这当差，也不是说走就能走的。所以还请你替我问问赵总管，我心里非常着急！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 2:
        	if ( who->get_level() >= 80 && !who->get_legend(TASK_38,13) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_38,13);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,50,"身世之谜" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"身世之谜");
        	}
        	break;
	case 3:
		if ( who->get_level() >= 100 && who->get_legend(TASK_38,25) && !who->get_legend(TASK_38,26) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    本来我就早想下挑战书给他们了，没想到被他们抢先一步，好，这封挑战书我接下了！\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
		break;
        case 4:
		if ( who->get_level() >= 100 && who->get_legend(TASK_38,25) && !who->get_legend(TASK_38,26) )
		{
        		if (TASK_LEGEND_D->check_task_item(who,"齐国守卫的挑战书",1) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_38,26);
			who->add_exp(42000);
			who->add_potential(600);
			who->add_cash(40000);
			send_user(who,"%c%s",';',"挑战 经验 42000 潜能 600 金钱 40000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,77,"" );
        	} 
        	break; 
	case 5:
		if ( who->get_level() >= 110 && who->get_legend(TASK_38,29) && !who->get_legend(TASK_38,30) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我是不会去的！我生是秦国的人，死也是秦国的鬼！\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
		break;
        case 6:
		if ( who->get_level() >= 110 && who->get_legend(TASK_38,29) && !who->get_legend(TASK_38,30) )
		{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_38,30);
			who->add_exp(48000);
			who->add_potential(610);
			who->add_cash(45000);
			send_user(who,"%c%s",';',"挖掘人才 经验 48000 潜能 610 金钱 45000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,66,"" );
        	} 
        	break; 
        case 99:
        	GUARDER_D->do_look( who, me ); 
        	break;     
        }
}