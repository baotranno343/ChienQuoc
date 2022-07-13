
#include <npc.h>
#include <city.h>
#include <task.h>
#include <ansi.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 5415; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("吕不韦");
        set_city_name("赵国");
        set_2( "talk", ([
                "welcome"	: (: do_welcome :),
        ]) );
	set("mpLegend2",([0:({32*19+23,32*19+30,32*20+3,}),]));
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
        if ( who->get_legend(TASK_19,22)&&!who->get_legend(TASK_19,23) ) 
		tmp += sprintf(ESC HIY "谈谈\ntalk %x# welcome.1\n",getoid(this_object())); 
        if ( (who->get_legend(TASK_19,23)&&!who->get_legend(TASK_19,24)) || (who->get_legend(TASK_19,24)&&!who->get_legend(TASK_19,25)) ) 
		tmp += sprintf(ESC HIY "赵姬\ntalk %x# welcome.1\n",getoid(this_object())); 
        if ( who->get_legend(TASK_19,29)&&!who->get_legend(TASK_19,30) ) 
		tmp += sprintf(ESC HIY "宝剑\ntalk %x# welcome.1\n",getoid(this_object())); 
        if ( (who->get_legend(TASK_19,30)&&!who->get_legend(TASK_20,1)) || (who->get_legend(TASK_20,1)&&!who->get_legend(TASK_20,3)) ) 
		tmp += sprintf(ESC HIY "清场\ntalk %x# welcome.1\n",getoid(this_object())); 
 
	send_user(who,"%c%c%w%s",':',3,get_char_picid(),sprintf( "%s：\n    "+"最近为某件事有点伤神啊。\n" ,get_name(),getoid(me)) +
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
        	if ( who->get_legend(TASK_19,22)&&!who->get_legend(TASK_19,23) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    月出皎兮。佼人僚兮。舒窈纠兮。劳心悄兮。月出皓兮。佼人懰兮。舒忧受兮。劳心慅兮。月出照兮。佼人燎兮。舒夭绍兮。劳心惨兮……\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_19,23)&&!who->get_legend(TASK_19,24) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哎，我所心忧的，乃是一个女子啊，我自从在紫烟楼听过她的歌，见过她的舞，日日魂牵梦绕，哪一日没有去到紫烟楼见到她就会心神不宁，如此娇柔可人儿，我只恨不得她时时都伴我身边，但是这位歌姬却是个高傲之人，她在紫烟楼也只是挂个牌而已，多少王孙公子都欲讨她回家却被她婉言相拒，我想征服她的心，才能真正得到这个倾城的佳人，想我行商之前也是一方游侠，粗粗通一点诗文而已，我委托我手下匠人专门打造了这个凤蝶佩，刻上了我少年时一首小诗，你把这个礼物送给赵姬，希望她能明白我的真心，她就在邯郸东郊。\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_19,24)&&!who->get_legend(TASK_19,25) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看来是落花有意，流水无情啊，不然那赵姬为什么不托你带个信给我。\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_19,29)&&!who->get_legend(TASK_19,30) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈！我明白她的意思了！我得快快准备，可能还需要你的帮助。\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
		else if (who->get_legend(TASK_19,30)&&!who->get_legend(TASK_20,1))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    这赵姬送我宝剑的意思……，嘿嘿，你去赵长城给我清场吧，我和她需要一个安静的地方面谈。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_20,1)&&!who->get_legend(TASK_20,2) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    距我和赵姬约好的时间越来越近了，还是早点去清场吧。\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_20,2)&&!who->get_legend(TASK_20,3) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    多谢你帮了我这么多的忙，现在你可以休息下了。\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
				
	       	break;
        case 2:
        	if( who->get_legend(TASK_19,22)&&!who->get_legend(TASK_19,23) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_19,23);
			who->add_exp(3800);
			who->add_potential(170);
			who->add_cash(3600);
			send_user(who,"%c%s",';',"找吕不韦谈谈 经验 3800 潜能 170 金钱 3600");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QINGUO,22,"" );
			me->do_welcome(1);
        	}
        	break;
        case 3:
        	if( who->get_legend(TASK_19,23)&&!who->get_legend(TASK_19,24) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		item = new("item/98/0088");
        		p = item->move(who,-1);
        		if ( !p )
        		{
        			destruct(item);
        			send_user(who,"%c%s",'!',"你携带的物品太多了");	
        			return ;
        		}
        		item->add_to_user(p);
        		who->set_legend(TASK_19,24);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"赵国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,36,"赵姬" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"赵姬");
        	}
        	break;
        case 4:
        	if( who->get_legend(TASK_19,29)&&!who->get_legend(TASK_19,30) )
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"宝剑",1) != 1 )
        			return;
        		TASK_LEGEND_D->give_item(who,"item/product/65065",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_19,30);
			who->add_exp(3800);
			who->add_potential(177);
			who->add_cash(3600);
			send_user(who,"%c%s",';',"宝剑 经验 3800 潜能 177 金钱 3600 紫焰项链图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,38,"" );
        		me->do_welcome(1);
        	}
        	break;
        case 5:
        	if( who->get_legend(TASK_19,30)&&!who->get_legend(TASK_20,1) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_20,1);
        		who->delete_save_2("lbwdaodunbing");
        		who->delete_save_2("lbwjiandunbing");
        		who->delete_save_2("lbwgongbing");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_ZHAOGUO,"赵国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,39,"清场" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"清场");
        	}
        	break;
        case 6:
        	if( who->get_legend(TASK_20,2)&&!who->get_legend(TASK_20,3) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_20,3);
        		who->delete_save_2("lbwdaodunbing");
        		who->delete_save_2("lbwjiandunbing");
        		who->delete_save_2("lbwgongbing");
			who->add_exp(12000);
			who->add_potential(730);
			who->add_cash(18000);
			send_user(who,"%c%s",';',"清场 经验 12000 潜能 730 金钱 18000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_ZHAOGUO,39,"" );
        	}
        	break;        	
        }
}
