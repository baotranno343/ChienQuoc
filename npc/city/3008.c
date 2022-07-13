
// 自动生成：/make/npc/make8008

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>

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
        set_name("Triệu Quốc Giám Ngục Quan");
        set_city_name("Triệu Quốc");

        set_2( "talk", ([
                "faling"        : (: do_faling :),
                 "accept_task"	: (: accept_task :),
                "welcome"	: (: do_welcome :),
        ]) );
 	set("mpLegend2",([0:({32*42+17,32*43+14,})]));
        setup();
}

string get_master() { return CITY_ZHAO->get_master(); }
string get_master_2() { return CITY_ZHAO->get_master_2(); }
string get_master_3() { return CITY_ZHAO->get_master_3(); }

void do_look( object who )
{
	string tmp="";
	object me = this_object();
	
	if ( who->get_legend(TASK_42,16) && !who->get_legend(TASK_42,17) )
		tmp += sprintf(ESC HIY "除掉刺客\ntalk %x# welcome.1\n",getoid(me));
	if ( who->get_legend(TASK_42,17) && !who->get_legend(TASK_42,20) )
		tmp += sprintf(ESC HIY "寻回地图\ntalk %x# welcome.1\n",getoid(me));
	if ( who->get_legend(TASK_42,20) && !who->get_legend(TASK_42,21) )
		tmp += sprintf(ESC HIY "禀报赵王\ntalk %x# welcome.1\n",getoid(me));
	if ( who->get_legend(TASK_43,13) && !who->get_legend(TASK_43,14) )
		tmp += sprintf(ESC HIY "寻回名单\ntalk %x# welcome.6\n",getoid(me));
	if ( who->get_legend(TASK_43,14) && !who->get_legend(TASK_43,15) )
		tmp += sprintf(ESC HIY "完成使命\ntalk %x# welcome.6\n",getoid(me));

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
           
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
        case 1:
        	if ( who->get_legend(TASK_42,16) && !who->get_legend(TASK_42,17) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    啊，刺客居然如此无法无天，居然出了这么大的纰漏，连王府路线图都被别人弄了去，事情可就麻烦了。幸好义士先把刺客头目抓住了，我们得赶紧想办法补救才是。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_42,17) && !who->get_legend(TASK_42,18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    刺客必定会将王府路线图这种重要的东西藏在自己很快能拿到的地方，那刺客活动之处一定藏有王府路线图，你前去天门阵三层北部一带寻找，他们一定会小心收藏，一定会在他们的某个宝箱里。\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_42,18) && !who->get_legend(TASK_42,19) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    若不是考虑到派兵搜索打草惊蛇，会被贼子们转移图纸，我哪里用得着你这么个笨手笨脚的家伙！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_42,19) && !who->get_legend(TASK_42,20) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    终于可以暂且舒一口气！\n"ESC"接受任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_42,20) && !who->get_legend(TASK_42,21) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这次夭折的刺杀行动充分暴露了我国在王府保卫工作方面的巨大漏洞，本官为未能肃清匪类深刻检讨，同时请你进宫代我面奏大王，一方面希望能够加强保密工作和严格人员准入制度，一方面也要严格纪律性，严防玩忽职守，尸位素餐，导致我国大王安全受到严重威胁的事件再次发生，如若是因为人手不足，更应该严格筛选一批政治过硬，作风优良，武力强健的护卫充实我王的保卫工作。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));

        	break; 
	case 2:
        	if ( who->get_legend(TASK_42,16) && !who->get_legend(TASK_42,17) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_42,17);
			who->add_exp(97000);
			who->add_potential(1650);
			who->add_cash(88000);
			send_user(who,"%c%s",';',"除掉刺客 经验 97000 潜能 1650 金钱 88000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,80,"" );
  			me->do_welcome(1);
	      	}
        	break; 
	case 3:
		if ( who->get_legend(TASK_42,17) && !who->get_legend(TASK_42,18) )
		{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_42,18);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,81,"寻回地图" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"寻回地图");
        	}
		break;
	case 4:
        	if ( who->get_legend(TASK_42,19) && !who->get_legend(TASK_42,20) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"王府路线图",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_42,20);
			who->add_exp(99000);
			who->add_potential(1600);
			who->add_cash(86000);
			send_user(who,"%c%s",';',"寻回地图 经验 99000 潜能 1600 金钱 86000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,81,"" );
  			me->do_welcome(1);
	      	}
        	break; 
	case 5:
		if ( who->get_legend(TASK_42,20) && !who->get_legend(TASK_42,21) )
		{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_42,21);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,82,"禀报赵王" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"禀报赵王");
        	}
		break;
        case 6:
        	if ( who->get_legend(TASK_43,13) && !who->get_legend(TASK_43,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    唉，何其不幸，为官必当通知家属，为他们妥善安排后事！\n"ESC"完成任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_43,14) && !who->get_legend(TASK_43,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    此事终于水落石出，但是结果真是让人扼腕叹息，治下竟有此等穷凶极恶之徒，更有怪力乱神的方士之辈。我写了封案情奏章禀报大王，你代我转交一下吧。\n"ESC"接受任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));

		break;
	case 7:
        	if ( who->get_legend(TASK_43,13) && !who->get_legend(TASK_43,14) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"失踪人员名单",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_43,14);
			who->add_exp(110000);
			who->add_potential(1850);
			who->add_cash(93000);
			send_user(who,"%c%s",';',"寻回名单 经验 110000 潜能 1850 金钱 93000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,91,"" );
  			me->do_welcome(6);
	      	}
        	break; 
	case 8:
		if ( who->get_legend(TASK_43,14) && !who->get_legend(TASK_43,15) )
		{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
        		TASK_LEGEND_D->give_item(who,"item/98/0211",1);  
        		who->set_legend(TASK_43,15);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,92,"完成使命" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"完成使命");
        	}
		break;
        case 99:
        	WARDER_D->do_look( who, me ); 
        	break;
        }
}