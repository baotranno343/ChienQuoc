
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
        set_name("Ngụy Quốc Ngự Sử");
	set_real_name("Ngụy Bạt");
        set_city_name("Ngụy Quốc");

        set_2( "talk", ([
                "elect"         : (: do_elect :),
                "vote"          : (: do_vote :),
                "score"         : (: do_score :),
                "welcome"	: (: do_welcome :),
        ]) );
//        set("level",100);
//        set("legend",({32*35+15}));
 	set("mpLegend",([100:({32*35+15}),]));
 	set("mpLegend2",([0:({32*35+14,32*35+24}),]));
        setup();
}

string get_master() { return CITY_WEI->get_master(); }
string get_master_2() { return CITY_WEI->get_master_2(); }
string get_master_3() { return CITY_WEI->get_master_3(); }

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( who->get_legend(TASK_35,13) && !who->get_legend(TASK_35,14) )
		tmp += sprintf(ESC HIY "解除奇事\ntalk %x# welcome.1\n",getoid(me));
	if ( who->get_level() >= 100 && !who->get_legend(TASK_35,15) )
		tmp += sprintf(ESC HIY "探明原因\ntalk %x# welcome.3\n",getoid(me));
	if ( who->get_legend(TASK_35,23) && !who->get_legend(TASK_35,24) )
		tmp += sprintf(ESC HIY "通报情况\ntalk %x# welcome.3\n",getoid(me));
	if ( who->get_legend(TASK_35,24) && !who->get_legend(TASK_35,25) )
		tmp += sprintf(ESC HIY "禀告魏王\ntalk %x# welcome.3\n",getoid(me));

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
        	if ( who->get_legend(TASK_35,13) && !who->get_legend(TASK_35,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呵呵，我就知道你办事得力。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));

        	break;

        case 2:
        	if ( who->get_legend(TASK_35,13) && !who->get_legend(TASK_35,14) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
			TASK_LEGEND_D->give_item(who,"item/final/91/1813",2);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_35,14);
			who->add_exp(78000);
			who->add_potential(1100);
			who->add_cash(68000);
			send_user(who,"%c%s",';',"解除奇事 经验 78000 潜能 1100 金钱 68000 六神丹 2");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,56,"" );
        	}
        	break;
        case 3:
        	if ( who->get_level() >= 100 && !who->get_legend(TASK_35,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    最近魏老汉又有奏报，说城西临河镇又出现了同上次相似的事件，但是元凶已死，怎么会又出现了，莫非还有同党？你去找魏老汉详细询问一下事情经过。\n"ESC"接受任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_35,23) && !who->get_legend(TASK_35,24) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    收到，本官必定会仔细遴选一名得力的官员治理临河。\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_35,24) && !who->get_legend(TASK_35,25) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈哈，我刚刚又得到魏老汉找人转告的消息，原来此前石大龙一案，真的事有乾坤，石大龙伏案附近找到了一个名叫乾坤袋的玩意，后来有高人说出此袋可装容大许多的物品，而且毫无负重，此等宝物我一俟高人研究出了使用方法就给我王送去，你先去通报一声，让他高兴一下。\n"ESC"接受任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
	case 4:
        	if ( who->get_level() >= 100 && !who->get_legend(TASK_35,15) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_35,15);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,57,"探明原因" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"探明原因");
        	}
        	break; 
        case 5:
        	if ( who->get_legend(TASK_35,23) && !who->get_legend(TASK_35,24) ) 
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_35,24);
			who->add_exp(80000);
			who->add_potential(1150);
			who->add_cash(70000);
			send_user(who,"%c%s",';',"通报情况 经验 80000 潜能 1150 金钱 70000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,60,"" );
			me->do_welcome(3);
        	}
        	break;
	case 6:
        	if ( who->get_legend(TASK_35,24) && !who->get_legend(TASK_35,25) ) 
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_35,25);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,61,"禀告魏王" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"禀告魏王");
        	}
        	break;
        case 99:	
		INQUISITOR_D->do_look( who, me); 
        	break;
        }
}      