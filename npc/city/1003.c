
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
        set_name("Tề Quốc Tài Chính Quan");
	set_real_name("Điền Đan");
        set_city_name("Tề Quốc");

        set_2( "talk", ([
                "info"          : (: do_info :),
                "tax"           : (: do_tax :),
                "salary"        : (: do_salary :),
                "cheque"        : (: do_cheque :),
                "comput"        : (: do_comput :),
                "welcome"	: (: do_welcome :),
        ]) );
	set("mpLegend2",([0:({32*9+20,32*9+25,32*29+22,32*38+22,}),]));
        setup();
}

string get_master() { return CITY_QI->get_master(); }
string get_master_2() { return CITY_QI->get_master_2(); }
string get_master_3() { return CITY_QI->get_master_3(); }

void do_look( object who )
{
	int id;
	string tmp="";
	object me = this_object();
	
	id = getoid(me);
	if ( who->get_legend(TASK_09,19) && !who->get_legend(TASK_09,20) )
	{
		tmp = sprintf(ESC HIY "赵的求助\ntalk %x# welcome.1\n",id);
	}
	if ( who->get_legend(TASK_09,20) && !who->get_legend(TASK_09,22) )
	{
		tmp = sprintf(ESC HIY "周子的劝说\ntalk %x# welcome.1\n",id);
	}
	if ( who->get_legend(TASK_09,24) && !who->get_legend(TASK_09,25) )
	{
		tmp = sprintf(ESC HIY "周子的信物\ntalk %x# welcome.1\n",id);
	}
	if ( who->get_legend(TASK_09,25) && !who->get_legend(TASK_09,26) )
	{
		tmp = sprintf(ESC HIY "回复齐总管\ntalk %x# welcome.1\n",id);
	}
	if ( who->get_legend(TASK_29,21) && !who->get_legend(TASK_29,22) )
	{
		tmp = sprintf(ESC HIY "水落石出\ntalk %x# welcome.6\n",id);
	}
	if ( who->get_legend(TASK_29,22) && !who->get_legend(TASK_29,23) )
	{
		tmp = sprintf(ESC HIY "寻找宝物\ntalk %x# welcome.6\n",id);
	}
        if ( who->get_level() >= 100 && who->get_legend(TASK_38,21) && !who->get_legend(TASK_38,22) ) 
		tmp += sprintf(ESC HIY "换份工作\ntalk %x# welcome.9\n",getoid(this_object())); 

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
        	if ( who->get_legend(TASK_09,19) && !who->get_legend(TASK_09,20) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这事有点棘手，我国与赵是盟友，若不帮赵国，于情于理都说不过去，但若帮了赵国，势必会削弱本国自身的国力与经济，如若赵败于长平，秦来攻击我国，到时处境可能有点不妙，这事我还得听听周子的意见！\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_09,20) && !who->get_legend(TASK_09,21) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    关于赵求助之事有点棘手，恐怕我一人也拿不定主意，周子是我王一直信任的人，恐怕还得听听他的意见，看他有何好的对策，你去替我询问他吧！周子最近前往鄱阳湖观景，大概在鄱阳亭吧！\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_09,21) && !who->get_legend(TASK_09,22) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    快去快回，情况紧急啊！\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_09,24) && !who->get_legend(TASK_09,25) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    好一个唇亡齿寒！周子果然是聪明人！你速去回复齐总管，过两日，待我们准备妥当后，自当将粮食运去长平。\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_09,25) && !who->get_legend(TASK_09,26) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    周子的唇亡齿寒论果然是一针见血！你速去回复齐总管，过两日，待我们准备妥当后，自当将粮食运去长平。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));

        	break;

        case 2:
        	if ( who->get_legend(TASK_09,19) && !who->get_legend(TASK_09,20) )
        	{
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_09,20);
			who->add_exp(2500);
			who->add_potential(60);
			who->add_cash(1800);
			send_user(who,"%c%s",';',"唇亡齿寒（1） 经验 2500 潜能 60 金钱 1800");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,1,"" );
			me->do_welcome(1);
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_09,20) && !who->get_legend(TASK_09,21) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_09,21);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,2,"唇亡齿寒（2）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"唇亡齿寒（2）");
        	}
        	break;
 	case 4:
        	if ( who->get_legend(TASK_09,24) && !who->get_legend(TASK_09,25) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"稻子",9) != 1 )
        			return;
        		TASK_LEGEND_D->task_finish(who);
        		who->set_legend(TASK_09,25);
			who->add_exp(3000);
			who->add_potential(95);
			who->add_cash(2200);
			send_user(who,"%c%s",';',"唇亡齿寒（3） 经验 3000 潜能 95 金钱 2200");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,3,"" );
			me->do_welcome(1);
        	}
        	break;
        case 5:
        	if ( who->get_legend(TASK_09,25) && !who->get_legend(TASK_09,26) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_09,26);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,4,"唇亡齿寒（4）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"唇亡齿寒（4）");
        	}
        	break;
        case 6:
        	if ( who->get_legend(TASK_29,21) && !who->get_legend(TASK_29,22) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哦！是齐总管介绍你来的，看来你还真不简单。\n"ESC"完成任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_29,22) && !who->get_legend(TASK_29,23) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哎，那可是不祥之物啊，既然你坚持要要，我也不阻拦你，只是忠告你如果家中出现闹鬼就要快快将它抛弃，美丽的往往充满了危险啊，千万不要因为一时的贪欲而造成家人的不幸，我堂哥家的事情你也知道了吧，哎，我也不好多说了，自求多福吧。它就在将军古墓的二层的小箱子里，上面为防万一我封了小符咒，你打开的时候站远点小心应该没有什么大碍。\n"ESC"接受任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(),getoid(me)));
        	

	    	break;
        case 7:
        	if ( who->get_legend(TASK_29,21) && !who->get_legend(TASK_29,22) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_29,22);
			who->add_exp(52000);
			who->add_potential(720);
			who->add_cash(54000);
			send_user(who,"%c%s",';',"水落石出 经验 52000 潜能 720 金钱 54000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,28,"" );
			me->do_welcome(6);
        	}
        	break; 
	case 8:
        	if ( who->get_legend(TASK_29,22) && !who->get_legend(TASK_29,23) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_29,23);
 			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"Tề Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,29,"寻找宝物" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"寻找宝物");
        	}
        	break;
        case 9:
	        if ( who->get_level() >= 100 && who->get_legend(TASK_38,21) && !who->get_legend(TASK_38,22) ) 
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    是的，近期有此打算，如果他有意，那你叫他亲自来找我，我还得看他体格够不够强壮！\n"ESC"完成任务\ntalk %x# welcome.10\n"ESC"离开", me->get_name(),getoid(me)));
		break;		
        case 10:
        	if ( who->get_level() >= 100 && who->get_legend(TASK_38,21) && !who->get_legend(TASK_38,22) ) 
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_38,22);
			who->add_exp(38000);
			who->add_potential(600);
			who->add_cash(35000);
			send_user(who,"%c%s",';',"换份工作 经验 38000 潜能 600 金钱 35000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_WEIGUO,67,"" );
        	}
        	break;

        case 99:	
		FINANCE_D->do_look( who, me); 
        	break;
        }
}
