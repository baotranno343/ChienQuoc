
// 自动生成：/make/npc/make8014

#include <npc.h>
#include <city.h>
#include <ansi.h>
#include <task.h>

#define GUARDER_D       "/inh/city/guarder"

inherit OFFICER;

void do_enter();
void do_record();

// 函数：获取人物造型
int get_char_picid() { return 5209; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Ngụy Quốc Thủ Vệ");
        set_city_name("Ngụy Quốc");

        set_2( "talk", ([
                "enter"         : (: do_enter :),
                "record"	: (: do_record :),
                "welcome"	: (: do_welcome :),
        ]) );
        set("out", 11);
        set("in", 13);
//        set("level",24);
//        set("legend",({32*6+7}));
 	set("mpLegend",([20:({32*6+7}),]));
 	set("mpLegend2",([20:({32*6+9}),]));
        setup();
}

string get_master() { return CITY_WEI->get_master(); }
string get_master_2() { return CITY_WEI->get_master_2(); }
string get_master_3() { return CITY_WEI->get_master_3(); }

void do_look( object who )
{ 
	string tmp="";
	object me = this_object();
	if ( who->get_level() >= 20 && (!who->get_legend(TASK_06,7) || !who->get_legend(TASK_06,9)))
	{
		tmp = sprintf(ESC HIY "英雄梦\ntalk %x# welcome.1\n",getoid(me));
	}

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
        int flag,p;
        object who,item,obj;  
        string cmd1;
           
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >= 20 && !who->get_legend(TASK_06,7)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    见过了将军驰骋沙场的英勇，从小便梦想身披英雄甲驰骋在沙场之上！可这个英雄梦却并没有那么容易实现，我想我需要做好充足的准备，当然，强健的体魄是最重要的，但是，除了锻炼身体外，我急切地想得到一套英雄甲，有人说在马踏湖的三贤亭见过英雄甲，从我这里出发，穿过马陵道与白马庄就到马踏湖了，如果你脚程快，我估计半个时辰不到你就能找到了。\n    你找来了英雄甲，等于圆了我半个梦，我一定不会亏待你的。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_06,7) && !who->get_legend(TASK_06,8) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来我这辈子是别想实现我的这个英雄梦了，还是老老实实站好我的岗吧！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_06,8) && !who->get_legend(TASK_06,9) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你真的给我找来了英雄甲？太好了，我真实地感觉到我离实现梦想又近了一步。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 2:
        	if ( who->get_level() >= 20 && !who->get_legend(TASK_06,7)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_06,7);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,21,"英雄梦" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"英雄梦");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_06,8) && !who->get_legend(TASK_06,9) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"英雄甲",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_06,9);
			who->add_exp(1500);
			who->add_potential(60);
			who->add_cash(1200);
			send_user(who,"%c%s",';',"英雄梦 经验 1500 潜能 60 金钱 1200");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,21,"" );
        	}
        	break;
        case 99:
        	GUARDER_D->do_look( who, me ); 
        	break;
        }
}