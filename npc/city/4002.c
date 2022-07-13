
// 自动生成：/make/npc/make8002

#include <npc.h>
#include <city.h>
#include <task.h>
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
        set_name("Ngụy Quốc Đại Tướng Quân");
	set_real_name("Tấn Bỉ");
        set_city_name("Ngụy Quốc");

        set_2( "talk", ([
                "patrol"        : (: do_patrol :),
                "soldier"       : (: do_soldier :),
                "armor"         : (: do_armor :),
                "welcome"	: (: do_welcome :),
            //    "defence"	: (: do_defence :),
        ]) );
//	set("level",85);
//	set("legend",({32*29+7})); 
 	set("mpLegend",([85:({32*29+7})]));
 	set("mpLegend2",([85:({32*29+9})]));
        setup();
}

string get_master() { return CITY_WEI->get_master(); }
string get_master_2() { return CITY_WEI->get_master_2(); }
string get_master_3() { return CITY_WEI->get_master_3(); }

//void do_defence(string arg) { "/sys/party/defence"->do_defence(this_player(), this_object(), arg); }

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( (who->get_level() >= 85 && !who->get_legend(TASK_29,7)) || (who->get_legend(TASK_29,7) && !who->get_legend(TASK_29,9)) )
	{
		tmp += sprintf(ESC HIY "石狮\ntalk %x# welcome.1\n",getoid(me));
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
        int flag,i,size,p,amount;
        object who,item, *inv;     
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if (who->get_level() >= 85 && !who->get_legend(TASK_29,7))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    将军古墓有一种诡异的机关，他们外形就是石狮，但是里面藏了好多厉害的毒针以及古怪的机活，进入的人往往以为他们只是装饰而疏忽大意，结果许多人命丧黄泉，最近大王派王储进去历练一番，但是我唯恐这类石狮误伤了公子，你先去扫除20个石狮，这样子王储就安全多了。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_29,7) && !who->get_legend(TASK_29,8) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来我应该多找几个人一起进将军古墓消灭他们，单凭你一个人的力量远远不够啊！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_29,8) && !who->get_legend(TASK_29,9) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果有可能的话，希望你能叫上你的朋友一起来帮助我。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 2:
        	if (who->get_level() >= 85 && !who->get_legend(TASK_29,7))
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_29,7);
        		who->delete_save("wgdjjshisi");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_WEIGUO,"Ngụy Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,32,"石狮" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"石狮");
        	}
        	break; 
        case 3:
        	if ( who->get_legend(TASK_29,8) && !who->get_legend(TASK_29,9) )
        	{
        		who->delete_save("wgdjjshisi");
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_29,9);
			who->add_exp(52000);
			who->add_potential(720);
			who->add_cash(48000);
			send_user(who,"%c%s",';',"石狮 经验 52000 潜能 720 金钱 48000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,32,"" );
        	}
        	break;   
   
 	case 99:
 		GENERAL_D->do_look( who, me); 
 		break;
        }
}