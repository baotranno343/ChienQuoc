
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
        set_name("Hàn Quốc Thương Nhân");
	set_real_name("Vương An");
        set_city_name("Hàn Quốc");

        set_2( "talk", ([
                "good"          : (: do_good :),
                "welcome"	: (: do_welcome :),
        ]) );
//        set("level",79);
//        set("legend",({32*26+10}));
 	set("mpLegend",([75:({32*26+10})]));
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
                "01" : "/item/99/9921",
                "02" : "/item/99/9922",
                "03" : "/item/99/9923",
        ]) );
        set_2( "list", ([
                "01" : 600,
                "02" : 500,
                "03" : 100,
        ]) );
}

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( who->get_level() >= 75 && !who->get_legend(TASK_26,10) )
		tmp += sprintf(ESC HIY "商人哭诉\ntalk %x# welcome.1\n",getoid(me));

	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_normal_word(me) + "\n"ESC"交易\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		JOB_TRADER_D->do_look( who, me ); 
	
}
void do_good( string arg ) { JOB_TRADER_D->do_good( this_player(), this_object(), arg ); }

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
        	if ( who->get_level() >= 75 && !who->get_legend(TASK_26,10) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我有一个侄子叫林为，本来林为跟我一样是一个出色的商人。但是在几个月之前林为与他的妻子到马踏湖游玩的时候，遇上了一个会操纵死灵的土匪打劫，不但林为的钱财被抢劫一空，林为的妻子还被那土匪残忍地杀死了。从此林为一直郁郁寡欢，终日以酒消愁。我不忍心我的侄子变得如此颓废，尽管那土匪现在藏身在妖物满布的灵谷洞，估计即使是官府也难以奈何他。但是我不可以让我侄子的妻子死得这么冤枉，这是我写的状纸，你替我把它交给韩国御史郑国吧。我无论如何也要为我的侄子讨回一个公道！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
	       	break;
        case 2 :
        	if ( who->get_level() >= 75 && !who->get_legend(TASK_26,10) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		item = new("item/98/0123");
        		if ( !item )
        			return ;
        		p = item->move(who,-1);
        		if ( !p )
        		{
        			destruct(item);
        			send_user(who,"%c%s",'!', "你携带的物品太多了");
        			return;
        		}
        		item->add_to_user(p);
        		who->set_legend(TASK_26,10);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,31,"商人哭诉" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"商人哭诉");
        	}
        	break;
    
        case 99:
        	JOB_TRADER_D->do_look( who, me ); 
        	break;
        }
}