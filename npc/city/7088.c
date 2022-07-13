
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
        set_name("Yên Quốc Thương Nhân");
	set_real_name("Kinh Kha");
        set_city_name("Yên Quốc");

        set_2( "talk", ([
                "good"          : (: do_good :),
                "welcome"	: (: do_welcome :),
        ]) );
//        set("level",54);
//        set("legend",({32*16+1}));
	set("mpLegend",([50:({32*16+1}),]));
        reset();

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
                "01" : "/item/99/9971",
                "02" : "/item/99/9972",
                "03" : "/item/99/9973",
        ]) );
        set_2( "list", ([
                "01" : 500,
                "02" : 400,
                "03" : 100,
        ]) );
}

void do_good( string arg ) { JOB_TRADER_D->do_good( this_player(), this_object(), arg ); }

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( ( who->get_level() >= 50 && !who->get_legend(TASK_16,1) ) || ( who->get_legend(TASK_16,1) && !who->get_legend(TASK_16,2) ) )
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
        	if ( who->get_level() >= 50 && !who->get_legend(TASK_16,1) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    现在生意都不好做，我想找个人合伙，与我一起做生意，这样风险会小点，你去帮我问问赵国商人，看他对这个计划持怎样的态度。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_16,1) && !who->get_legend(TASK_16,2) )
        		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你是没找到赵国商人，还是他不同意呢？？\n"ESC"离开", me->get_name()));
        	break;
        case 2 :
        	if ( who->get_level() >= 50 && !who->get_legend(TASK_16,1) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_16,1);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YANGUO,"Yên Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YANGUO,35,"合伙做生意" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"合伙做生意");
        	}
        	break;
    
        case 99:
        	JOB_TRADER_D->do_look( who, me ); 
        	break;
        }
}