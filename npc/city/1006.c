
// 自动生成：/make/npc/make8006

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>

#define INQUISITOR_D    "/inh/city/inquisitor"

inherit OFFICER;

void do_elect( string arg );
void do_vote( string arg );
void do_score( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5102; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Tề Quốc Ngự Sử");
	set_real_name("Duẫn Văn");
        set_city_name("Tề Quốc");

        set_2( "talk", ([
                "elect"         : (: do_elect :),
                "vote"          : (: do_vote :),
                "score"         : (: do_score :),
                "welcome"	: (: do_welcome :),
        ]) );
//	set("level",88);
//	set("legend",({32*30+8,}));
 	set("mpLegend",([85:({32*30+8,32*30+20}),]));
 	set("mpLegend2",([85:({32*30+2,32*30+29}),]));
        setup();
}

string get_master() { return CITY_QI->get_master(); }
string get_master_2() { return CITY_QI->get_master_2(); }
string get_master_3() { return CITY_QI->get_master_3(); }

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( who->get_legend(TASK_30,1) && !who->get_legend(TASK_30,2) )
		tmp += sprintf(ESC HIY "将军信函\ntalk %x# welcome.1\n",getoid(me));
	if ( who->get_legend(TASK_30,2) && !who->get_legend(TASK_30,3) )
		tmp += sprintf(ESC HIY "民间探访\ntalk %x# welcome.1\n",getoid(me));
	if ( who->get_level() >= 85 && !who->get_legend(TASK_30,8) )
		tmp += sprintf(ESC HIY "询查原因\ntalk %x# welcome.4\n",getoid(me));
	if ( who->get_level() >= 85 && !who->get_legend(TASK_30,20) )
		tmp += sprintf(ESC HIY "深入民间\ntalk %x# welcome.6\n",getoid(me));
	if ( who->get_legend(TASK_30,28) && !who->get_legend(TASK_30,29) )
		tmp += sprintf(ESC HIY "除掉恶匪\ntalk %x# welcome.6\n",getoid(me));
	if ( who->get_legend(TASK_30,29) && !who->get_legend(TASK_24,29) )
		tmp += sprintf(ESC HIY "禀告齐王\ntalk %x# welcome.6\n",getoid(me));

	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		INQUISITOR_D->do_look( who, this_object() ); 
	
}
void do_elect( string arg ) { INQUISITOR_D->do_elect( this_player(), this_object(), arg ); }
void do_vote( string arg ) { INQUISITOR_D->do_vote( this_player(), this_object(), arg ); }
void do_score( string arg ) { INQUISITOR_D->do_score( this_player(), this_object(), arg ); }
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
        	if ( who->get_legend(TASK_30,1) && !who->get_legend(TASK_30,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这事不好办啊！\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_30,2) && !who->get_legend(TASK_30,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    为今之计只得求助于民间流言了，看有没有什么线索，你先去问问齐国百姓唐茂吧，看有没有什么乡野传言。\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));

        	break;

        case 2:
        	if ( who->get_legend(TASK_30,1) && !who->get_legend(TASK_30,2) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"将军信函",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_30,2);
			who->add_exp(58000);
			who->add_potential(770);
			who->add_cash(51000);
			send_user(who,"%c%s",';',"将军信函 经验 58000 潜能 770 金钱 51000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,31,"" );
			me->do_welcome(1);
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_30,2) && !who->get_legend(TASK_30,3) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_30,3);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,32,"民间探访" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"民间探访");
        	}
        	break;
        case 4:
        	if ( who->get_level() >= 85 && !who->get_legend(TASK_30,8) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    最近有件案子让人头痛啊，民事纠纷最是难断是非，最近为了争地，李屠和雷霸天斗得不亦乐乎，里正也不知道如何插手，据说李屠如今争不过，被赶到河这边来了，你去他那里调查调查到底怎么回事。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 5:
        	if ( who->get_level() >= 85 && !who->get_legend(TASK_30,8) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_30,8);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,35,"询查原因" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"询查原因");
        	}
        	break;
        case 6:
        	if ( who->get_level() >= 85 && !who->get_legend(TASK_30,20) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    最近本官心情好，想深入民间做点好事好得点风评，你去市井找百姓打听打听，最近他们有没有什么不棘手的下情禀报，你觉得本官能够不费力达成的就尽管答应他们吧。\n"ESC"接受任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_30,28) && !who->get_legend(TASK_30,29) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈，你果然是我的好助力，以后跟着我混，我吃肉决不会让你喝汤！\n"ESC"完成任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_30,29) && !who->get_legend(TASK_24,29) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    那个马小七本来是一个汪洋大盗，还曾经伙同他人盗过王宫，他狡猾得很，一直没法把他抓捕归案，大王也很生气，如今终于将他除了，还顺便解决了民众的困难，真是一举两得啊！你赶紧进宫禀报大王，让他也高兴一下。\n"ESC"接受任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 7:
        	if ( who->get_level() >= 85 && !who->get_legend(TASK_30,20) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_30,20);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,40,"深入民间" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"深入民间");
        	}
        	break;
        case 8:
        	if ( who->get_legend(TASK_30,28) && !who->get_legend(TASK_30,29) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
			TASK_LEGEND_D->give_item(who,"item/product/64158",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_30,29);
			who->add_exp(68000);
			who->add_potential(830);
			who->add_cash(56000);
			send_user(who,"%c%s",';',"除掉恶匪 经验 68000 潜能 830 金钱 56000 斩侯鞋图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,43,"" );
			me->do_welcome(6);
        	}
        	break;
        case 9:
        	if ( who->get_legend(TASK_30,29) && !who->get_legend(TASK_24,29) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_24,29);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,44,"禀告齐王" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"禀告齐王");
        	}
        	break;
        case 99:	
		INQUISITOR_D->do_look( who, me); 
        	break;
        }
}        	