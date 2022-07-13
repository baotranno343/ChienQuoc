
// 自动生成：/make/npc/make8002

#include <npc.h>
#include <city.h>
#include <task.h>
#include <equip.h>
#include <ansi.h>

#define GENERAL_D       "/inh/city/general"

inherit OFFICER;

void do_patrol( string arg );
void do_soldier( string arg );
void do_armor( string arg );
//void do_defence( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5201; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Hàn Quốc Đại Tướng Quân");
	set_real_name("Hàn Cừ");
        set_city_name("Hàn Quốc");

        set_2( "talk", ([
                "patrol"        : (: do_patrol :),
                "soldier"       : (: do_soldier :),
                "armor"         : (: do_armor :),
                "welcome"	: (: do_welcome :),
            //    "defence"	: (: do_defence :),
        ]) );
//        set("level",20);
//        set("legend",({32*37+19}));
 	set("mpLegend",([15:({32*37+19,}),20:({32*4+29}),70:({32*23+1,}),]));
 	set("mpLegend2",([20:({32*4+30}),70:({32*23+3,}),]));
        setup();
}

string get_master() { return CITY_HAN->get_master(); }
string get_master_2() { return CITY_HAN->get_master_2(); }
string get_master_3() { return CITY_HAN->get_master_3(); }

//void do_defence(string arg) { "/sys/party/defence"->do_defence(this_player(), this_object(), arg); }

void do_look( object who )
{
	string tmp="";
	object me = this_object();

	if ( who->get_level() >= 15 && !who->get_legend(TASK_37,19) )
		tmp += sprintf(ESC HIY "崔大官人的请柬\ntalk %x# welcome.8\n",getoid(me));
	
	if ( (who->get_level() >= 20 && !who->get_legend(TASK_04,29) ) || ( who->get_legend(TASK_04,29) && !who->get_legend(TASK_04,30)) )
	{
		tmp += sprintf(ESC HIY "将军之难\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( (who->get_level() >= 70 && !who->get_legend(TASK_23,1) ) || ( who->get_legend(TASK_23,1) && !who->get_legend(TASK_23,3)) )
	{
		tmp += sprintf(ESC HIY "泄密之灾\ntalk %x# welcome.5\n",getoid(me));
	}
//	if ("/sys/sys/count"->get_war_flag1()||"/sys/party/defence"->get_count())
//		tmp += sprintf(ESC HIY "Chiến Trường Thủ Thành\ntalk %x# defence.1\n",getoid(me));
	
	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		GENERAL_D->do_look( who, this_object() ); 
	
}
void do_patrol( string arg ) { GENERAL_D->do_patrol( this_player(), this_object(), arg ); }
void do_soldier( string arg ) { GENERAL_D->do_soldier( this_player(), this_object(), arg ); }
void do_armor( string arg ) { GENERAL_D->do_armor( this_player(), this_object(), arg ); }
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
        	if ( who->get_level() >= 20 && !who->get_legend(TASK_04,29) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    上次在首阳山的聚贤坡操练军队，突遇黑色旋风，不知是妖魔做法还是天生异象。慌忙撤退中本将军竟然不小心把调兵符弄丢了。这可如何是好？%s能帮我把那调兵符寻回来吗？\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),NPC_RANK_D->get_respect_2(who),getoid(me)));
		else if ( who->get_legend(TASK_04,29) && !who->get_legend(TASK_04,30) )
			me->do_welcome(4);
        	break;
        case 2:
        	if ( who->get_level() >= 20 && !who->get_legend(TASK_04,29) )
        	{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			who->delete_save("diaobingfu");
        		who->set_legend(TASK_04,29);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,15,"将军之难" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"将军之难");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_04,29) && !who->get_legend(TASK_04,30) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"调兵符",1) != 1 )
        			return;
        		TASK_LEGEND_D->give_item(who,"item/final/33/1703",3);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_04,30);
			who->delete_save("diaobingfu");
			who->delete_save_2("diaobingfu");
			who->add_exp(2200);
			who->add_potential(80);
			who->add_cash(1500);
			send_user(who,"%c%s",';',"将军之难 经验 2200 潜能 80 金钱 1500 豆腐干 3");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,15,"" );
        	}
        	break;
        case 4:
        	if ( !who->get_legend(TASK_04,29) || who->get_legend(TASK_04,30) )
        		return ;
        	if ( objectp(item=present("调兵符",who,1,MAX_CARRY)) && item->is_legend_item() == 1 )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这下太好了，%s本将军一定会好好酬谢于你！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),NPC_RANK_D->get_respect_2(who),getoid(me)));
		else
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来我只好向大王请罪去，希望大王能够宽恕于我。\n"ESC"离开", me->get_name()));
        	break;
        case 5:
        	if ( who->get_level() >= 70 && !who->get_legend(TASK_23,1) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    自从长平之战后，六国之中已经没有任何一国可以单独与秦国对抗了，秦国一直对其他六国虎视眈眈，有传闻说秦国的第一个目标就是我们韩国，最近在弯道那边好象有些不寻常的动向，一批密探已经到达那里，一定是秦国的密探已经在开始收集我国的军事情报了，为了防范秦国，我们先得把这批密探除掉，你去弯道去帮我把那批密探杀掉吧！事成后我一定禀明大王对你重重有赏。\n"ESC"接受任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_23,1) && !who->get_legend(TASK_23,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    希望可以在这批密探获得的我国情报之前尽快把他除掉，不然我们国家就危险了。\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_23,2) && !who->get_legend(TASK_23,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    虽然你把这批密探消灭了，但是有传闻说我们的军事资料已经送到咸阳了，看来我们要准备好与秦国一战了。你这次的功劳我已经禀告大王了，这是你的赏赐。\n"ESC"完成任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 6:
        	if ( who->get_level() >= 70 && !who->get_legend(TASK_23,1) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_23,1);
        		who->delete_save_2("hgdjjmitan");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,44,"泄密之灾" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"泄密之灾");
        	}
        	break;  
        case 7:
        	if ( who->get_legend(TASK_23,2) && !who->get_legend(TASK_23,3) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_23,3);
        		who->delete_save_2("hgdjjmitan");
			who->add_exp(25000);
			who->add_potential(430);
			who->add_cash(23000);
			send_user(who,"%c%s",';',"泄密之灾 经验 25000 潜能 430 金钱 23000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,44,"" );
        	}
        	break;
        case 8:
        	if ( who->get_level() >= 15 && !who->get_legend(TASK_37,19) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    听闻魏国的崔大官人是一个在行军作战方面不可多得的人才，虽然他失去了记忆，但是一个人的谋略是不可能失去的，所以我有意请他来我们军营做个师爷，只是不知道他是否会应承，现在我派你去魏国将这封请柬送给崔大官人，一定要亲手交给他本人，听到没！\n    崔大官人就居住在魏国的大梁城内。\n"ESC"接受任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));
		break;
        case 9:
        	if ( who->get_level() >= 15 && !who->get_legend(TASK_37,19) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
        		TASK_LEGEND_D->give_item(who,"item/98/0178",1);	
        		who->set_legend(TASK_37,19);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,48,"崔大官人的请柬" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"崔大官人的请柬");
        	}
        	break;
        case 99:	
		GENERAL_D->do_look( who, me); 
        	break;
        }
}
