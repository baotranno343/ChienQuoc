
// 自动生成：/make/npc/make8088

#include <npc.h>
#include <ansi.h>
#include <task.h>
#include <equip.h>

#define JOB_TRADER_D    "/inh/job/trader"

inherit OFFICER;
inherit "/inh/npc/trader";

void reset();
void do_good( string arg );
int is_self_look() { return 1;}

// 函数：获取人物造型
int get_char_picid() { return 5401; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Ngụy Quốc Thương Nhân");
	set_real_name("Khổng Thị");
        set_city_name("Ngụy Quốc");

        set_2( "talk", ([
                "good"          : (: do_good :),
                "welcome"	: (: do_welcome :),
        ]) );
        reset();
//	set("level",23);
//	set("legend",({32*5+25}));
 	set("mpLegend",([20:({32*5+25}),]));
 	set("mpLegend2",([90:({32*38+17}),20:({32*5+27}),]));
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
                "01" : "/item/99/9941",
                "02" : "/item/99/9942",
                "03" : "/item/99/9943",
        ]) );
        set_2( "list", ([
                "01" : 300,
                "02" : 200,
                "03" : 100,
        ]) );
}

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( ( who->get_level()>=20&&!who->get_legend(TASK_05,25)) || ( who->get_legend(TASK_05,25)&&!who->get_legend(TASK_05,27)) )
	{
		tmp = sprintf(ESC HIY "遗忘的誓言\ntalk %x# welcome.1\n",getoid(me));
	}
        if ( who->get_level() >= 90 && who->get_legend(TASK_38,17) && !who->get_legend(TASK_38,18) ) 
		tmp += sprintf(ESC HIY "询问价格\ntalk %x# welcome.4\n",getoid(me)); 

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
        object who,item;     
       	string *nTmp,tmp;     
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >= 20 && !who->get_legend(TASK_05,25)  )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你认识劫匪李大山吗？我很小的时候就在我父亲面前立下誓言，一定要除掉这个作恶多端的土匪！一晃这么多年过去了，但我还未实现当年立下的誓言，看来我得靠别人的帮助才能实现了。\n    这些年来，那个劫匪不仅抢走了太多的财物，还害死了很多贫苦的百姓，希望你能伸出正义之手，将这个劫匪李大山除掉！\n    他现在正在白马庄的白马湖附近游玩，从马踏湖与马陵道都可以到白马庄。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_05,25) && !who->get_legend(TASK_05,26) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来我还是找别人来帮忙算了！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_05,26) && !who->get_legend(TASK_05,27) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下不光是那个害人的劫匪被除掉了，我多年来的誓言也完成了，非常感谢！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
			
        	break;
        case 2:
        	if ( who->get_level() >= 20 && !who->get_legend(TASK_05,25)  )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_05,25);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,17,"遗忘的誓言" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"遗忘的誓言");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_05,26) && !who->get_legend(TASK_05,27) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),0,20,WEAPON_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			TASK_LEGEND_D->give_item(who,tmp,1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_05,27);
			who->add_exp(1300);
			who->add_potential(70);
			who->add_cash(1200);
			send_user(who,"%c%s",';',sprintf("遗忘的誓言 经验 1300 潜能 70 金钱 1200 %s 1",tmp->get_name()));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,17,"" );
        	}
        	break;
        case 4:
        	if ( who->get_level() >= 90 && who->get_legend(TASK_38,17) && !who->get_legend(TASK_38,18) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    太抱歉了，那批布我已经卖出去了！\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
		break;        	
        case 5:
        	if ( who->get_level() >= 90 && who->get_legend(TASK_38,17) && !who->get_legend(TASK_38,18) ) 
		{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_38,18);
			who->add_exp(33000);
			who->add_potential(420);
			who->add_cash(25000);
			send_user(who,"%c%s",';',"询问价格 经验 33000 潜能 420 金钱 25000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,75,"" );
        	}
		break;
        case 99:
        	JOB_TRADER_D->do_look( who, me ); 
        	break;
        }
}