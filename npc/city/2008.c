
// 自动生成：/make/npc/make8008

#include <npc.h>
#include <city.h>
#include <ansi.h>
#include <task.h>
#include <equip.h>
#define WARDER_D        "/inh/city/warder"

inherit OFFICER;

void do_faling();
void accept_task();

// 函数：获取人物造型
int get_char_picid() { return 5102; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Hàn Quốc Giám Ngục Quan");
        set_city_name("Hàn Quốc");

        set_2( "talk", ([
                "faling"        : (: do_faling :),
                 "accept_task"	: (: accept_task :),
                 "welcome"          : (: do_welcome :),
        ]) );
//	set("level",19);
//	set("legend",({32*4+26}));
	set("mpLegend",([15:({32*4+26}),20:({32*5+4})]));
	set("mpLegend2",([15:({32*4+28}),20:({32*5+6})]));
        setup();
}

string get_master() { return CITY_HAN->get_master(); }
string get_master_2() { return CITY_HAN->get_master_2(); }
string get_master_3() { return CITY_HAN->get_master_3(); }

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( (who->get_level() >= 15 && !who->get_legend(TASK_04,26) ) || ( who->get_legend(TASK_04,26) && !who->get_legend(TASK_04,28)) )
	{
		tmp = sprintf(ESC HIY "追捕重犯\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( (who->get_level() >= 20 && !who->get_legend(TASK_05,4) ) || ( who->get_legend(TASK_05,4) && !who->get_legend(TASK_05,6)) )
	{
		tmp += sprintf(ESC HIY "明正刑典\ntalk %x# welcome.4\n",getoid(me));
	}
	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		WARDER_D->do_look( who, this_object() ); 
	
}
void do_faling() { WARDER_D->do_faling( this_player(), this_object() ); }

void accept_task() { WARDER_D->accept_task( this_player(), this_object() );}
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
       	string *nTmp,tmp;   
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_level() >= 15 && !who->get_legend(TASK_04,26) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    大侠你终于出现了！监狱之中，不乏有高手异人。最近，有一名在押的重犯趁看守不备，越狱逃跑了。这事如果让大王知道了定会怪罪于我，本人官职定将不保。%s能否帮我将此重犯杀掉？我一定重谢你。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),NPC_RANK_D->get_respect_2(who),getoid(me)));
		else if ( who->get_legend(TASK_04,27) && !who->get_legend(TASK_04,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    多谢%s出手相助，不然真不知该如何向大王交差，本官一定会报答%s的恩德。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),cmd1=NPC_RANK_D->get_respect_2(who),cmd1,getoid(me)));
        	else if ( who->get_legend(TASK_04,26) && !who->get_legend(TASK_04,27) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    出现此类事情是本官的失职，本官只好主动向大王请罪。\n"ESC"离开", me->get_name()));
        	break; 
        case 2:
        	if ( who->get_level() >= 15 && !who->get_legend(TASK_04,26) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_04,26);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,12,"追捕重犯" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"追捕重犯");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_04,27) && !who->get_legend(TASK_04,28) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
        		nTmp = WEAPON_FILE->get_family_equip(who->get_fam_name(),who->get_gender(),20,WAIST_TYPE);
        		tmp = nTmp[random(sizeof(nTmp))];
        		if ( !stringp(tmp) )
        			return ;
			item = new(tmp);
			item->set_record(1);
			ITEM_EQUIP_D->init_equip_prop_3(item);
			p = item->move(who,-1);
			item->add_to_user(p);

			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_04,28);
			who->add_exp(1900);
			who->add_potential(70);
			who->add_cash(1600);
			send_user(who,"%c%s",';',sprintf("追捕重犯 经验 1900 潜能 70 金钱 1600 %s 1",tmp->get_name()));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,12,"" );
        	}
        	break;    
        case 4:
        	if ( who->get_level() >= 20 && !who->get_legend(TASK_05,4) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    大侠你终于出现了，最近一个将要被问斩的犯人许横刀，被他的同伙劫走了。听闻许横刀现在正在虎牢关一带逃亡。这许横刀欺男霸女，做尽了坏事。为明正刑典，惩恶扬善，还望%s前去将他除掉。我代韩国的民众先在这里谢谢你了。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),NPC_RANK_D->get_respect_2(who),getoid(me)));
		else if ( who->get_legend(TASK_05,5) && !who->get_legend(TASK_05,6) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    多谢%s相助，这次你可立了大功，本官一定会奖赏你。\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),cmd1=NPC_RANK_D->get_respect_2(who),getoid(me)));
        	else if ( who->get_legend(TASK_05,4) && !who->get_legend(TASK_05,5) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来我得请求大王派重兵前去捉拿，定要将他缉拿归案。\n"ESC"离开", me->get_name()));
        	break; 
        case 5:
        	if ( who->get_level() >= 20 && !who->get_legend(TASK_05,4) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_05,4);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,14,"明正刑典" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"明正刑典");
        	}
        	break;
        case 6:
        	if ( who->get_legend(TASK_05,5) && !who->get_legend(TASK_05,6) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/product/62006",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_05,6);
			who->add_exp(2100);
			who->add_potential(90);
			who->add_cash(1600);
			send_user(who,"%c%s",';',"明正刑典 经验 2100 潜能 90 金钱 1600 铜剑图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,14,"" );
        	}
        	break; 
        case 99:	
		WARDER_D->do_look( who, me); 
        	break;
        }
}