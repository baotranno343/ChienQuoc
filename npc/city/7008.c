
// 自动生成：/make/npc/make8008

#include <npc.h>
#include <city.h>
#include <ansi.h>
#include <task.h>

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
        set_name("Yên Quốc Giám Ngục Quan");
        set_city_name("Yên Quốc");

        set_2( "talk", ([
                "faling"        : (: do_faling :),
                 "accept_task"	: (: accept_task :),
                 "welcome"          : (: do_welcome :),
        ]) );
//	set("level",43);
//	set("legend",({32*10+26}));
	set("mpLegend",([40:({32*10+26}),55:({32*16+11})]));
	set("mpLegend2",([40:({32*10+28}),55:({32*16+13})]));
        setup();
}

string get_master() { return CITY_YAN->get_master(); }
string get_master_2() { return CITY_YAN->get_master_2(); }
string get_master_3() { return CITY_YAN->get_master_3(); }

void do_look( object who ) 
{
	string tmp="";
	object me = this_object();
	
	if ( (who->get_level() >= 40 && !who->get_legend(TASK_10,26) ) || ( who->get_legend(TASK_10,26) && !who->get_legend(TASK_10,28)) )
	{
		tmp = sprintf(ESC HIY "千年之劫\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( (who->get_level() >= 55 && !who->get_legend(TASK_16,11) ) || ( who->get_legend(TASK_16,11) && !who->get_legend(TASK_16,13)) )
	{
		tmp += sprintf(ESC HIY "逍遥法外\ntalk %x# welcome.4\n",getoid(me));
	}
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
        	if ( who->get_level() >= 40 && !who->get_legend(TASK_10,26) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    传说长白山每千年便会出现一个劫难，而这个劫难需要武林中人团结起来，才能化解，根据最近我观测到的情况来看，这次劫数可能是长白山的绿壳蜘蛛要作乱，最近那边忽然多出了很多绿壳蜘蛛，你去看看，如果真是这样，你就消灭掉它们再回来告诉我吧！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_10,26) && !who->get_legend(TASK_10,27) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果你帮不上忙，可能我得另找其他的途径，千万不能让这劫数应现。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_10,27) && !who->get_legend(TASK_10,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来单单凭你一个人的力量还不足以消灭他们，你能号召更多的人来帮助我吗？\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break; 
        case 2:
        	if ( who->get_level() >= 40 && !who->get_legend(TASK_10,26) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_10,26);
        		who->delete_save_2("lkzhizhu");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,16,"千年之劫" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"千年之劫");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_10,27) && !who->get_legend(TASK_10,28) )
        	{
        		who->delete_save_2("lkzhizhu");
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_10,28);
			who->add_exp(4800);
			who->add_potential(150);
			who->add_cash(3600);
			send_user(who,"%c%s",';',"千年之劫 经验 4800 潜能 150 金钱 3600");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,16,"" );
        	}
        	break;    
        case 4:
        	if ( who->get_level() >= 55 && !who->get_legend(TASK_16,11) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    本官手上绝对不允许出现任何一个犯人逍遥法外，你去燕长城给我杀20个枪兵，宁可误杀一千，也不放过一个。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_16,11) && !who->get_legend(TASK_16,12) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果你办不到这事，我就去另请高明了！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_16,12) && !who->get_legend(TASK_16,13) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我敢肯定，你杀的20个枪兵里，绝对有一个是前天的那个杀人犯。\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
        	break; 
        case 5:
        	if ( who->get_level() >= 55 && !who->get_legend(TASK_16,11) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_16,11);
        		who->delete_save_2("ygqianbing");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,36,"逍遥法外" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"逍遥法外");
        	}
        	break;
        case 6:
        	if ( who->get_legend(TASK_16,12) && !who->get_legend(TASK_16,13) )
        	{
        		who->delete_save_2("ygqianbing");
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_16,13);
			who->add_exp(6800);
			who->add_potential(260);
			who->add_cash(5600);
			send_user(who,"%c%s",';',"逍遥法外 经验 6800 潜能 260 金钱 5600");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,36,"" );
        	}
        	break;    
        case 99:	
		WARDER_D->do_look( who, me); 
        	break;
        }
}