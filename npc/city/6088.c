
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
void do_welcome(string arg);
// 函数：获取人物造型
int get_char_picid() { return 5401; }

// 函数：构造处理
void create()
{
        set_name("Sở Quốc Thương Nhân");
	set_real_name("Khuất Giới");
        set_city_name("Sở Quốc");

        set_2( "talk", ([
                "good"          : (: do_good :),
                "welcome"	: (: do_welcome :),
        ]) );
        reset();
//	set("level",13);
//	set("legend",({32*3+11,}) );
	set("mpLegend",([10:({32*3+11}),30:({32*8+25})]));
	set("mpLegend2",([30:({32*8+27})]));
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
                "01" : "/item/99/9961",
                "02" : "/item/99/9962",
                "03" : "/item/99/9963",
        ]) );
        set_2( "list", ([
                "01" : 80,
                "02" : 50,
                "03" : 10,
        ]) );
}

void do_look( object who ) 
{
	string tmp="";
	object me = this_object();
	
	if ( who->get_level() >= 10 && who->get_legend(TASK_NEWBIE_03,11)==0 )
	{
		 tmp = sprintf(ESC HIY "买椟还珠\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( ( who->get_level() >= 30 && !who->get_legend(TASK_08,25) ) || ( who->get_legend(TASK_08,25) && !who->get_legend(TASK_08,27) ) )
	{
		tmp += sprintf(ESC HIY "湘妃林的鬼火\ntalk %x# welcome.3\n",getoid(me));
	}
	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_normal_word(me) + "\n"ESC"交易\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		JOB_TRADER_D->do_look( who, this_object() ); 
	
}

void do_good( string arg ) { JOB_TRADER_D->do_good( this_player(), this_object(), arg ); }

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        int flag;
        object who;     
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >= 10 && who->get_legend(TASK_NEWBIE_03,11)==0 )
        		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    嘿～～年轻人！我见你年纪轻轻就在外面游历，见识应该不少吧。听说过南海明珠吗？这可是个好东西！\n    近来，珠宝行情一路上涨，特别是那颗南海明珠更是炒到了天价，凑巧的是这颗珍珠刚好被我在齐国的兄弟收购了，他为这南海明珠可花了不少银子，当然也想卖个好价钱，他一直想找个盒子来装这颗南海明珠，但是一直都不能寻得合适的，你去看看能不能帮上他，他可是腰缠万贯的大富豪，不会亏待你的。\n    他就在齐国的临淄城内，过了桥在王府外你就能看到了。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 2:
        	if ( who->get_level() >= 10 && who->get_legend(TASK_NEWBIE_03,11)==0 )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_NEWBIE_03,11);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,7,"买椟还珠(1)" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"买椟还珠(1)");
        	}
        	break;
        case 3:
        	if ( who->get_level() >= 30 && !who->get_legend(TASK_08,25) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我是一个生意人，长年累月在外面过着近乎流浪的生活，经常为了多赚点钱，天色很晚了才回家。俗话说，夜路走多了，总会遇到鬼。鬼我是没遇见，鬼火倒是见过一次。\n    我记得那天已经很晚了，我挑着担子穿过大别山的湘妃林，准备回家泡个热水澡，好好休息，突然，我发现那树林后面似乎有闪闪的星光，荧绿荧绿的，直觉告诉我，那一定是鬼火。\n    曾经听村里的老人家说过，在湘妃林一带有一个夜浮鬼，经常出来作恶，你去调查一下吧。\n"ESC"接受任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_08,25) && !who->get_legend(TASK_08,26) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    下次做生意再也不从那条路上走了，免得被那恶鬼撞见。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_08,26) && !who->get_legend(TASK_08,27) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呵呵，以后从那里走再也不用担心了。\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 4:
        	if ( who->get_level() >= 30 && !who->get_legend(TASK_08,25) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_08,25);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_CHUGUO,"Sở Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,21,"湘妃林的鬼火" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"湘妃林的鬼火");
        	}
        	break;
        case 5:
        	if ( who->get_legend(TASK_08,26) && !who->get_legend(TASK_08,27) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/final/16/1637",5);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_08,27);
			who->add_exp(2500);
			who->add_potential(90);
			who->add_cash(2000);
			send_user(who,"%c%s",';',"湘妃林的鬼火 经验 2500 潜能 90 金钱 2000 硝石粉 5");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_CHUGUO,21,"" );
        	}
        	break;   
        case 99:
        	JOB_TRADER_D->do_look( who, me ); 
        	break;
        }
}