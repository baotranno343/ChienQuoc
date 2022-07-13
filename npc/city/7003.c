
// 自动生成：/make/npc/make8003

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>

#define FINANCE_D       "/inh/city/finance"
#define FINANCE_2_D     "/inh/city/finance2"
#define JOB_TRADER_D    "/inh/job/trader"

inherit OFFICER;

void do_info( string arg );
void do_tax( string arg );
void do_salary( string arg );
void do_cheque( string arg );
void do_comput( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5102; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Yên Quốc Tài Chính Quan");
	set_real_name("Thái Tử Đan");
        set_city_name("Yên Quốc");

        set_2( "talk", ([
                "info"          : (: do_info :),
                "tax"           : (: do_tax :),
                "salary"        : (: do_salary :),
                "cheque"        : (: do_cheque :),
                "comput"        : (: do_comput :),
                "welcome"	: (: do_welcome :),
        ]) );
	set("mpLegend",([50:({32*14+18}),]));
	set("mpLegend2",([50:({32*14+20}),]));
        setup();
}

string get_master() { return CITY_YAN->get_master(); }
string get_master_2() { return CITY_YAN->get_master_2(); }
string get_master_3() { return CITY_YAN->get_master_3(); }

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( ( who->get_level() >= 50 && !who->get_legend(TASK_14,18) ) || ( who->get_legend(TASK_14,18) && !who->get_legend(TASK_14,20) ) )
	{
		tmp = sprintf(ESC HIY "偷钱的笨熊\ntalk %x# welcome.1\n",getoid(me));
	}

	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		FINANCE_D->do_look( who, this_object()); 
	
}
void do_info( string arg ) { FINANCE_D->do_info( this_player(), this_object(), arg ); }
void do_tax( string arg ) { FINANCE_D->do_tax( this_player(), this_object(), arg ); }
void do_salary( string arg ) { FINANCE_D->do_salary( this_player(), this_object(), arg ); }

void do_cheque( string arg ) { JOB_TRADER_D->do_cheque( this_player(), this_object(), arg ); }    // ## 3 ##
void do_comput( string arg ) { FINANCE_2_D->do_comput( this_player(), this_object(), arg ); }    // ## 2 ##

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        int flag,p;
        object who,item;     
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >= 50 && !who->get_legend(TASK_14,18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    居然有笨熊老去国库偷钱！\n    今天无意中进国库检查，居然看见15只笨熊在里面闹翻了天！那群守卫都是吃屎的，真是气死我了！你去玉柱峰给我杀掉他们！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_14,18) && !who->get_legend(TASK_14,19) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我托你办的事呢？办好了吗？\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_14,19) && !who->get_legend(TASK_14,20) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这群该死的笨熊，死有余辜呀！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 2:
        	if ( who->get_level() >= 50 && !who->get_legend(TASK_14,18) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_14,18);
        		who->delete_save_2("tqbengxiong");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,29,"偷钱的笨熊" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"偷钱的笨熊");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_14,19) && !who->get_legend(TASK_14,20) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_14,20);
        		who->delete_save_2("tqbengxiong");
			who->add_exp(6000);
			who->add_potential(245);
			who->add_cash(4900);
			send_user(who,"%c%s",';',"偷钱的笨熊 经验 6000 潜能 245 金钱 4900");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,29,"" );
        	}
        	break;
        case 99:	
		FINANCE_D->do_look( who, me); 
        	break;
        }
}