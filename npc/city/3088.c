
// 自动生成：/make/npc/make8088

#include <npc.h>
#include <task.h>
#include <ansi.h>

#define JOB_TRADER_D    "/inh/job/trader"

inherit OFFICER;
inherit "/inh/npc/trader";
int is_self_look() { return 1;}

void reset();
void do_good( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5401; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Triệu Quốc Thương Nhân");
	set_real_name("Quách Tung");
        set_city_name("Triệu Quốc");

        set_2( "talk", ([
                "good"          : (: do_good :),
                "welcome"	: (: do_welcome :),
        ]) );
        reset();
 	set("mpLegend2",([0:({32*16+2,}),]));
        setup();
}

// 函数：复位处理
void reset()
{
	object me = this_object();
	me->set("reset_time", time());
        set_buy_rate( random(1001) );
        set_sell_rate( random(1001) );

        set_2( "good", ([
                "01" : "/item/99/9931",
                "02" : "/item/99/9932",
                "03" : "/item/99/9933",
        ]) );
        set_2( "list", ([
                "01" : 300,
                "02" : 50,
                "03" : 20,
        ]) );
}

void do_good( string arg ) { JOB_TRADER_D->do_good( this_player(), this_object(), arg ); }

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if (  who->get_legend(TASK_16,1) && !who->get_legend(TASK_16,2)  )
		tmp += sprintf(ESC HIY "合伙做生意\ntalk %x# welcome.1\n",getoid(me));

	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_normal_word(me) + "\n"ESC"交易\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		JOB_TRADER_D->do_look( who, this_object() ); 
	
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        int flag;
        object who,item;     
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_legend(TASK_16,1) && !who->get_legend(TASK_16,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我也正有此意，过几日我就起程去和燕国商人谈谈这件事。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 2:
        	if ( who->get_legend(TASK_16,1) && !who->get_legend(TASK_16,2) )
        	{
			who->add_exp(5500);
			who->add_potential(230);
			who->add_cash(5000);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_16,2);
			send_user(who,"%c%s",';',"合伙做生意 经验 5500 潜能 230 金钱 5000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,35,"" );
			me->do_welcome(1);
        	}
        	break;
    
        case 99:
        	JOB_TRADER_D->do_look( who, me ); 
        	break;
        }
}