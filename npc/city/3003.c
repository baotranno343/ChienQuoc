
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
        set_name("Triệu Quốc Tài Chính Quan");
	set_real_name("Lăng Tương Như");
        set_city_name("Triệu Quốc");

        set_2( "talk", ([
                "info"          : (: do_info :),
                "tax"           : (: do_tax :),
                "salary"        : (: do_salary :),
                "cheque"        : (: do_cheque :),
                "comput"        : (: do_comput :),
                "welcome"	: (: do_welcome :),
        ]) );
//	set("level",55);
//	set("legend",({32*16+8}));
 	set("mpLegend",([55:({32*16+8}),]));
 	set("mpLegend2",([55:({32*16+10}),]));
        setup();
}

string get_master() { return CITY_ZHAO->get_master(); }
string get_master_2() { return CITY_ZHAO->get_master_2(); }
string get_master_3() { return CITY_ZHAO->get_master_3(); }

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( ( who->get_level() >= 55 && !who->get_legend(TASK_16,8) ) || ( who->get_legend(TASK_16,8) && !who->get_legend(TASK_16,10) ) )
	{
		tmp = sprintf(ESC HIY "紧缩开支\ntalk %x# welcome.1\n",getoid(me));
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
        object who,item,obj;  
        string cmd1;
           
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
 	case 1:
        	if ( who->get_level() >=55 && !who->get_legend(TASK_16,8) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哦，我记得你！上次就是你去牧场帮赵国大将军李牧消灭了赵长城上的叛贼头目吧？他一直说你神勇呢！什么？不是你？汗～～原来我记错了。\n    不过没关系，既然你上次没帮我的忙，那这次帮我个小忙，不介意吧？为了缩减开支，本应派军队消灭的叛贼只能请人去做，你去赵长城上给我消灭15个刀盾兵吧，对你来说，应该是一点问题都没有的。\n    赶紧去吧，记得回来领报酬啊～\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_16,8) && !who->get_legend(TASK_16,9) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果没有人帮我，我就得申请出动军队了，唉，到时候财政怎么受得了哦。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_16,9) && !who->get_legend(TASK_16,10) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    能节约就节约吧，尽量不出动军队。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 2:
        	if( who->get_level() >=55 && !who->get_legend(TASK_16,8) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_16,8);
        		who->delete_save_2("zgdaobing");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,9,"紧缩开支" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"紧缩开支");
        	}
        	break;       
        case 3:
        	if ( who->get_legend(TASK_16,9) && !who->get_legend(TASK_16,10) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_16,10);
        		who->delete_save_2("zgdaobing");
			who->add_exp(6500);
			who->add_potential(265);
			who->add_cash(5800);
			send_user(who,"%c%s",';',"紧缩开支 经验 6500 潜能 265 金钱 5800");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,9,"" );
        	}
        	break;  
        case 99:
        	FINANCE_D->do_look( who, me); 
        	break;     
        }
}