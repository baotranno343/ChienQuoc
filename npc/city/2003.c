
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
        set_name("Hàn Quốc Tài Chính Quan");
	set_real_name("Hàn Phi");
        set_city_name("Hàn Quốc");

        set_2( "talk", ([
                "info"          : (: do_info :),
                "tax"           : (: do_tax :),
                "salary"        : (: do_salary :),
                "cheque"        : (: do_cheque :),
                "comput"        : (: do_comput :),
                "welcome"	: (: do_welcome :),
        ]) );
//	set("level",16);
//	set("legend",({32*4+1}));
	set("mpLegend",([15:({32*4+1}),]));
	set("mpLegend2",([0:({32*25+5,32*25+8,}),15:({32*4+3}),]));
        setup();
}

string get_master() { return CITY_HAN->get_master(); }
string get_master_2() { return CITY_HAN->get_master_2(); }
string get_master_3() { return CITY_HAN->get_master_3(); }

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( ( who->get_level() >= 15 && !who->get_legend(TASK_04,1) ) || ( who->get_legend(TASK_04,1) && !who->get_legend(TASK_04,3) ) )
	{
		tmp = sprintf(ESC HIY "失窃的库银\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( who->get_legend(TASK_25,4) && !who->get_legend(TASK_25,5) )
	{
		tmp += sprintf(ESC HIY "索取宝图\ntalk %x# welcome.4\n",getoid(me));
	}
	if ( (who->get_legend(TASK_25,5) && !who->get_legend(TASK_25,6)) || (who->get_legend(TASK_25,6) && !who->get_legend(TASK_25,8)) )
	{
		tmp += sprintf(ESC HIY "清除威胁\ntalk %x# welcome.4\n",getoid(me));
	}
	if ( who->get_legend(TASK_25,8) && !who->get_legend(TASK_25,9) )
	{
		tmp += sprintf(ESC HIY "寻根问底\ntalk %x# welcome.4\n",getoid(me));
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
        	if ( who->get_level() >= 15 && !who->get_legend(TASK_04,1) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    大侠你终于出现了！昨晚一个飞盗趁我库银兵守备不严，盗走了一箱黄金。现在大王还不知道此事，如果大王知道此事一定会撤了我的官职。还望%s替我追回那箱黄金，保着本人的官职，本官定有酬谢！\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),NPC_RANK_D->get_respect_2(who),getoid(me)));
		else if ( who->get_legend(TASK_04,2) && !who->get_legend(TASK_04,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呵呵……这下不用担心向大王交不了差了，本官一定会好好报答你的。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_04,1) && !who->get_legend(TASK_04,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来此事定要遭到大王责骂了……\n"ESC"离开", me->get_name()));
        	break;
        case 2:
        	if ( who->get_level() >= 15 && !who->get_legend(TASK_04,1) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_04,1);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,1,"失窃的库银" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"失窃的库银");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_04,2) && !who->get_legend(TASK_04,3) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"一箱黄金",1) != 1 )
        			return;
			TASK_LEGEND_D->give_item(who,"/item/91/9100",3);
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_04,3);
			who->add_exp(1200);
			who->add_potential(70);
			who->add_cash(1200);
			send_user(who,"%c%s",';',"失窃的库银 经验 1200 潜能 70 金钱 1200 行军散 3");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,1,"" );
        	}
        	break;
        case 4:
		if ( who->get_legend(TASK_25,4) && !who->get_legend(TASK_25,5) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哦！你是为那宝图而来，让我想想，这件事情好久没人提起，我都快把这件事情给忘记了。\n"ESC"完成任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_25,5) && !who->get_legend(TASK_25,6) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    不是我不愿意和你说这宝图事情，而是有个叫李三的劫盗威胁我。如果我将这宝图的事情说出去，他将会取我性命。你愿意前去灵谷洞一层将他杀掉吗？\n"ESC"接受任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_25,6) && !who->get_legend(TASK_25,7) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    宝图这件事关系我的性命，他不被除掉，我怎么敢随便说。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_25,7) && !who->get_legend(TASK_25,8) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    好了，让我想想，我把这事情的真相和你说吧！\n"ESC"完成任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_25,8) && !who->get_legend(TASK_25,9) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    其实王府里面的那张藏宝图就在我们的韩总管身上，但是要他把藏宝图给你可不是一件容易的事。韩总管最近为着一些事烦恼，我想你想获得那张藏宝图的话或许这是一个机会，你先去跟他谈谈吧。\n"ESC"接受任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
        case 5:
        	if ( who->get_legend(TASK_25,4) && !who->get_legend(TASK_25,5) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_25,5);
			who->add_exp(31000);
			who->add_potential(480);
			who->add_cash(30000);
			send_user(who,"%c%s",';',"索取宝图 经验 31000 潜能 480 金钱 30000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,16,"" );
			me->do_welcome(4);
        	}
        	break;
        case 6:
        	if ( who->get_legend(TASK_25,5) && !who->get_legend(TASK_25,6) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_25,6);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,17,"清除威胁" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"清除威胁");
        	}
        	break;
        case 7:
        	if ( who->get_legend(TASK_25,7) && !who->get_legend(TASK_25,8) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_25,8);
			who->add_exp(30000);
			who->add_potential(490);
			who->add_cash(32000);
			send_user(who,"%c%s",';',"清除威胁 经验 30000 潜能 490 金钱 32000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,17,"" );
			me->do_welcome(4);
        	}
        	break;
        case 8:
        	if ( who->get_legend(TASK_25,8) && !who->get_legend(TASK_25,9) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_25,9);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,18,"寻根问底" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"寻根问底");
        	}
        	break;
        case 99:	
		FINANCE_D->do_look( who, me); 
        	break;
        }
}