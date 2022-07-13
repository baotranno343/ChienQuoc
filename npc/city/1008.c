
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
        set_name("Tề Quốc Giám Ngục Quan");
        set_city_name("Tề Quốc");

        set_2( "talk", ([
                "faling"        : (: do_faling :),
                 "accept_task"	: (: accept_task :),
                "welcome"	: (: do_welcome :),
        ]) );
//	set("level",75);
//	set("legend",({32*24+26}));
 	set("mpLegend",([75:({32*24+26,}),]));
 	set("mpLegend2",([75:({32*24+28,}),]));
        setup();
}

string get_master() { return CITY_QI->get_master(); }
string get_master_2() { return CITY_QI->get_master_2(); }
string get_master_3() { return CITY_QI->get_master_3(); }

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( (who->get_level() >= 75 && !who->get_legend(TASK_24,26) ) || ( who->get_legend(TASK_24,26) && !who->get_legend(TASK_24,28)) )
	{
		tmp += sprintf(ESC HIY "可怕的发现\ntalk %x# welcome.1\n",getoid(me));
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
        	if ( who->get_level() >= 75 && !who->get_legend(TASK_24,26) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    最近本国监狱里面发生了一场可怕的瘟疫，几乎监狱里面所有的人都感染了瘟疫，虽然我已经把监狱与外界隔离了，但是我担心瘟疫还是会有一天传染到监狱外面来。引起这场瘟疫的是在灵谷洞的疫鬼，只要把这些疫鬼杀掉，或许就可以令这场瘟疫平静下来，你去灵谷洞去把这些瘟疫的源头消灭掉吧！这些疫鬼一群一共是20个，把他们全部消灭掉后回来我这里，我会按照你的功劳给你报酬的。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_24,26) && !who->get_legend(TASK_24,27) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    现在监狱里面的瘟疫还是得不到控制，如果不消灭这群疫鬼，恐怕瘟疫还将蔓延下去。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_24,27) && !who->get_legend(TASK_24,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    现在监狱里面的瘟疫已经得到控制了，我想这是因为你已经把灵谷洞的疫鬼除掉了吧。这次的事情你是功劳最大者，这里是你的报酬，放心收下吧，我代表齐国上下感谢你。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break; 
        case 2:
        	if ( who->get_level() >= 75 && !who->get_legend(TASK_24,26) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_24,26);
        		who->delete_save_2("qgdygyigui");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,19,"可怕的发现" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"可怕的发现");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_24,27) && !who->get_legend(TASK_24,28) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/64135",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_24,28);
        		who->delete_save_2("qgdygyigui");
			who->add_exp(37000);
			who->add_potential(528);
			who->add_cash(35000);
			send_user(who,"%c%s",';',"可怕的发现 经验 37000 潜能 528 金钱 35000 倾露鞋图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,19,"" );
        	}
        	break;   

        case 99:
        	WARDER_D->do_look( who, me ); 
        	break;
        }
}