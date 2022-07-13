
// 自动生成：/make/npc/make8020

#include <npc.h>
#include <ansi.h>
#include <task.h>

#define INTERIOR_D      "/inh/city/interior"

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 0451; }
void do_welcome( string arg );

// 函数：师父识别
int is_master() { return 1; }

// 函数：师父识别(武教头)
int is_basic_master() { return 2; }

int is_self_look() { return 1; }

// 函数：小贩识别
int is_seller() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Hàn Quốc Công Tượng");
        set_real_name("May Mặc 49~58");
        set_city_name("Hàn Quốc");
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
//	set("level",20);
//	set("legend",({32*5+1}));
 	set("mpLegend",([20:({32*5+1}),]));
 	set("mpLegend2",([20:({32*5+3}),]));
	set_skill(0640, 39);
        set_2( "good", ([
                "01" : "/item/product/64070",
                "02" : "/item/product/64071",
                "03" : "/item/product/64072",
//                "04" : "/item/product/64073",
                "05" : "/item/product/64074",
                "06" : "/item/product/64075",
                "07" : "/item/product/64076",
                "08" : "/item/product/64077",
                "09" : "/item/product/64078",
                "10" : "/item/product/64079",
                "11" : "/item/product/64080",        
                "12" : "/item/product/64081",
                "13" : "/item/product/64082",
                "14" : "/item/product/64083",
                "15" : "/item/product/64084",      
                "16" : "/item/product/64085",
                "17" : "/item/product/64086",
                "18" : "/item/product/64087",
                "19" : "/item/product/64088",
                "20" : "/item/product/64089",
                "21" : "/item/product/64090",        
                "22" : "/item/product/64091",                                        
        ]) );		
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
	object me = this_object();
	if ( ( who->get_level() >= 20 && !who->get_legend(TASK_05,1) ) || ( who->get_legend(TASK_05,1) && !who->get_legend(TASK_05,3) ) )
	{
		tmp = sprintf(ESC HIY "解救工匠\ntalk %x# welcome.1\n",getoid(me));
	}
	tmp += sprintf(ESC"Học kĩ năng\nlearn ? %s\n", me->get_char_id());
	tmp += sprintf(ESC"Mua công thức May Mặc 49 - 58\nlist %s\n", me->get_char_id());
	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) ,get_name()));
	
}
int accept_object( object who, object obj ) { return INTERIOR_D->accept_object_2( who, this_object(), obj, 8 ); }

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
        	if ( who->get_level() >= 20 && !who->get_legend(TASK_05,1) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    大侠你终于出现了。那恶官马三，克扣我的工钱。我前去找他理论，谁知他不但不给我一分钱，还叫他的手下将我毒打一顿。马三还命我今天继续上工，我这今天要是去了，定不会活着回来。%s你可有办法救我一命吗？\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),NPC_RANK_D->get_respect_2(who),getoid(me)));
		else if ( who->get_legend(TASK_05,2) && !who->get_legend(TASK_05,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    呵呵，这下可好了！再也不用受那恶官欺负了。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_05,1) && !who->get_legend(TASK_05,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来我今天是在劫难逃啊！谁叫我的命苦呢？可怜我家还有妻儿老小啊！\n"ESC"离开", me->get_name()));
        	break; 
        case 2:
        	if ( who->get_level() >= 20 && !who->get_legend(TASK_05,1) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_05,1);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_HANGUO,"Hàn Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,13,"解救工匠" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"解救工匠");
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_05,2) && !who->get_legend(TASK_05,3) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
				return ;  
        		TASK_LEGEND_D->give_item(who,"item/final/15/1500",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_05,3);
			who->add_exp(2000);
			who->add_potential(80);
			who->add_cash(1800);
			send_user(who,"%c%s",';',"解救工匠 经验 2000 潜能 80 金钱 1800 初级血气 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_HANGUO,13,"" );
        	}
        	break;  
        }
}