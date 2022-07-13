
// 自动生成：/make/npc/make8010

#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>

#define GUARDER_D       "/inh/city/guarder"

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 0600; }
void do_welcome(string arg);

// 函数：构造处理
void create()
{
        set_name("Triệu Quốc Thủ Vệ");
        set_city_name("Triệu Quốc");
        set_2( "talk", ([
                "welcome"	: (: do_welcome :),
        ]) );
//        set("level",55);
//        set("legend",({32*16+3}));
	set("mpLegend",([55:({32*16+3}),80:({32*28+1})]));
	set("mpLegend2",([55:({32*16+5}),80:({32*28+3})]));
        setup();
}

string get_master() { return CITY_ZHAO->get_master(); }
string get_master_2() { return CITY_ZHAO->get_master_2(); }
string get_master_3() { return CITY_ZHAO->get_master_3(); }

void do_look( object who )
{ 
	string tmp="";
	object me = this_object();
	if ( (who->get_level() >= 55 && !who->get_legend(TASK_16,3)) || (who->get_legend(TASK_16,3)&&!who->get_legend(TASK_16,5)) )
	{
		tmp = sprintf(ESC HIY "拦路狗\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( (who->get_level() >= 80 && !who->get_legend(TASK_28,1)) || (who->get_legend(TASK_28,1) && !who->get_legend(TASK_28,3)))
	{
		tmp += sprintf(ESC HIY "雕刻\ntalk %x# welcome.4\n",getoid(me));
	}
	if ( sizeof(tmp) )
		send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"/quest/word"->get_country_word(me) + "\n"ESC"对话\ntalk %x# welcome.99\n",get_name(),getoid(me)) +
		tmp +
		ESC"离开");
	else
		GUARDER_D->do_look_3( who, me ); 
	
}

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
        	if ( who->get_level() >=55 && !who->get_legend(TASK_16,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这赵长城本是我国百姓外出的必经之道，可有人却打起了它的主意，收起了过路费，真是一群见钱眼开的拦路狗！\n    就是那批剑盾兵，将这条必经之道用栅栏拦住，寻常百姓要想从此路过，必须得留下买路钱，真是目无王法，还希望%s能伸张正义，为百姓撑腰，除掉这群拦路狗。\n"ESC"接受任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(), NPC_RANK_D->get_respect_2(who),getoid(me)));
		else if ( who->get_legend(TASK_16,3) && !who->get_legend(TASK_16,4) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    如果不尽快解决这件事，这百姓的出行就变得极为不方便了。\n"ESC"离开", me->get_name()));
		else if ( who->get_legend(TASK_16,4) && !who->get_legend(TASK_16,5) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    人作恶是终究会受到惩罚的。\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
	case 2:
        	if( who->get_level() >=55 && !who->get_legend(TASK_16,3) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_16,3);
        		who->delete_save_2("zgjianbing");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,7,"拦路狗" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"拦路狗");
        	}
        	break;       
        case 3:
        	if ( who->get_legend(TASK_16,4) && !who->get_legend(TASK_16,5) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_16,5);
        		who->delete_save_2("zgjianbing");
			who->add_exp(6500);
			who->add_potential(260);
			who->add_cash(5600);
			send_user(who,"%c%s",';',"拦路狗 经验 6500 潜能 260 金钱 5600");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,7,"" );
        	}
        	break;  
        case 4:
        	if ( who->get_level() >= 80 && !who->get_legend(TASK_28,1) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我亲戚是一个有名的雕刻大师，他雕刻出来的东西惟妙惟肖，贵族王室都奉为珍品，他最近答应我帮我做一件镇宅笔架，需要8块木板和3块玉石，而且说玉石需用死玉，木块需用尸木，都常吸取怨灵之气方能以毒攻毒，而这两种东西万人坑中寻找最易，不知壮士可有空去跑一番？\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_28,1) && !who->get_legend(TASK_28,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    既然你有勇气去万人坑，还是希望你能找来我要的木板与玉石。\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_28,2) && !who->get_legend(TASK_28,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    等到镇宅笔架做成安放的那天，我一定邀请前来参观。\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));

        	break;
	case 5:
        	if ( who->get_level() >= 80 && !who->get_legend(TASK_28,1) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_28,1);
        		who->delete_save("zgswmuban");
        		who->delete_save("zgswyushi");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"Triệu Quốc" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,45,"雕刻" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"雕刻");
        	}
        	break;
        case 6:
        	if ( who->get_legend(TASK_28,2) && !who->get_legend(TASK_28,3) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"木板",8) != 1 )
        			return;
        		if (TASK_LEGEND_D->check_task_item(who,"玉石",3) != 1 )
        			return;
        		TASK_LEGEND_D->give_item(who,"item/product/62073",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_28,3);
        		who->delete_save("zgswmuban");
        		who->delete_save("zgswyushi");
			who->add_exp(48600);
			who->add_potential(688);
			who->add_cash(46800);
			send_user(who,"%c%s",';',"雕刻 经验 48600 潜能 688 金钱 46800 大夏龙雀图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,45,"" );
        	}
        	break; 
        case 99:
        	GUARDER_D->do_look_3( who, me ); 
        	break;     
        }
}