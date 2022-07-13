
#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 6010; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("赵姬");
        set_city_name("赵国");
        set_2( "talk", ([
                "welcome"	: (: do_welcome :),
        ]) );
	set("mpLegend2",([0:({32*19+25,32*19+28,}),]));
        setup();
}

string get_master() { return CITY_QIN->get_master(); }
string get_master_2() { return CITY_QIN->get_master_2(); }
string get_master_3() { return CITY_QIN->get_master_3(); }

void do_look( object who )
{ 
	string tmp="";
	object me = this_object();
        tmp += CHAIN_D->get_chain_menu(who,me);
        if ( who->get_legend(TASK_19,24)&&!who->get_legend(TASK_19,25) ) 
		tmp += sprintf(ESC HIY "赵姬\ntalk %x# welcome.1\n",getoid(this_object())); 
        if ( (who->get_legend(TASK_19,25)&&!who->get_legend(TASK_19,26)) || (who->get_legend(TASK_19,26)&&!who->get_legend(TASK_19,28)) ) 
		tmp += sprintf(ESC HIY "合适的礼物\ntalk %x# welcome.1\n",getoid(this_object())); 
        if ( (who->get_legend(TASK_19,28)&&!who->get_legend(TASK_19,29)) || (who->get_legend(TASK_19,29)&&!who->get_legend(TASK_19,39)) ) 
		tmp += sprintf(ESC HIY "宝剑\ntalk %x# welcome.1\n",getoid(this_object())); 

	send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"小女子命苦，自小就被卖到青楼，但我是卖艺不卖身，如果不能遇到让我心仪的公子，我是不会……\n" ,get_name(),getoid(me)) +
		tmp +
		ESC"离开");

	
}

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
        	if ( who->get_legend(TASK_19,24)&&!who->get_legend(TASK_19,25) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    承蒙吕大人的厚爱，礼物我收下了，还想请你帮个忙。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_19,25)&&!who->get_legend(TASK_19,26) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    既然吕先生看得起小女子，妾身也当有所回报，听得赵长城有个兵士曾经得了一个宝剑，唤作韦剑，宝剑只能相佩者得之，我想请你取来送给吕先生，可以吗？\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_19,26)&&!who->get_legend(TASK_19,27) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    难道宝剑已经被别人拿走了么？\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_19,27)&&!who->get_legend(TASK_19,28) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    谢谢你帮我找来宝剑，可否再帮个忙，送给吕先生？\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_19,28)&&!who->get_legend(TASK_19,29) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    既然你已经找来了宝剑，那也请你将宝剑交给吕大人吧。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_19,29)&&!who->get_legend(TASK_19,30) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    赶快送过去，别弄丢了。\n"ESC"离开", me->get_name()));
 
	       	break;
        case 2:
        	if( who->get_legend(TASK_19,24)&&!who->get_legend(TASK_19,25) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"给赵姬的礼物",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_19,25);
			who->add_exp(3880);
			who->add_potential(175);
			who->add_cash(3600);
			send_user(who,"%c%s",';',"赵姬 经验 3880 潜能 175 金钱 3600");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,36,"" );
			me->do_welcome(1);
        	}
        	break;
        case 3:
        	if( who->get_legend(TASK_19,25)&&!who->get_legend(TASK_19,26) )
        	{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			who->set_legend(TASK_19,26);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"赵国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,37,"合适的礼物" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"合适的礼物");
        	}
        	break;
        case 4:
        	if( who->get_legend(TASK_19,27)&&!who->get_legend(TASK_19,28) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"宝剑",1) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_19,28);
			who->add_exp(4000);
			who->add_potential(188);
			who->add_cash(3700);
			send_user(who,"%c%s",';',"合适的礼物 经验 4000 潜能 188 金钱 3700");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,37,"" );
        		me->do_welcome(1);
        	}
        	break;
        case 5:
        	if( who->get_legend(TASK_19,28)&&!who->get_legend(TASK_19,29) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		item = new("item/98/0089");
        		p = item->move(who,-1);
        		if ( !p )
        		{
        			destruct(item);
        			send_user(who,"%c%s",'!',"你携带的物品太多了");	
        			return ;
        		}
        		item->add_to_user(p);
			who->set_legend(TASK_19,29);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"赵国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,38,"宝剑" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"宝剑");
        	}
        	break;
        }
}