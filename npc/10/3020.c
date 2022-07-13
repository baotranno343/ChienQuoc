
// 自动生成：/make/npc/make-collect

#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <task.h>
#include <music.h>

inherit OFFICER;

void do_welcome(string arg);

// 函数：获取人物造型
int get_char_picid() { return 0252; }

// 函数：构造处理
void create()
{
        set_name("Lôi Bá Thiên");

        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));      
	set("mpLegend2",([0:({32*30+11,32*30+14,32*30+17,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	object me=this_object();
	string tmp="";
        tmp += CHAIN_D->get_chain_menu(who,me);
	if ( who->get_legend(TASK_30,10) && !who->get_legend(TASK_30,11) )
	{
		tmp += sprintf(ESC HIY "明辨是非\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( (who->get_legend(TASK_30,11) && !who->get_legend(TASK_30,12)) || (who->get_legend(TASK_30,12) && !who->get_legend(TASK_30,14)) )
	{
		tmp += sprintf(ESC HIY "威慑对手\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( (who->get_legend(TASK_30,14) && !who->get_legend(TASK_30,15)) || (who->get_legend(TASK_30,15) && !who->get_legend(TASK_30,17)) )
	{
		tmp += sprintf(ESC HIY "铲除祸害\ntalk %x# welcome.1\n",getoid(me));
	}
	if ( who->get_legend(TASK_30,17) && !who->get_legend(TASK_30,18) )
	{
		tmp += sprintf(ESC HIY "驯服恶霸\ntalk %x# welcome.1\n",getoid(me));
	}
        send_user( who, "%c%s", ':', sprintf( "%s：\n    %s\n", get_name(),TASK_COLLECT_D->get_talk_string(0611))
        + tmp +
        ESC"离开"
         );
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
        	if ( who->get_legend(TASK_30,10) && !who->get_legend(TASK_30,11) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你是什么人，也想来管我们村的闲事?\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_30,11) && !who->get_legend(TASK_30,12) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈哈，河边这块地就是我家的，怎么了？要同我斗，告诉你，我有将军古墓四层的30个枪俑河30个弓箭石俑做守卫，你有本事先闯过他们的阵再来同我说话，哈哈！\n"ESC"接受任务\ntalk %x# welcome.3\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_30,12) && !who->get_legend(TASK_30,13) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你想管我的事，还嫩了点！\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_30,13) && !who->get_legend(TASK_30,14) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    啊，你小子还没有死？\n"ESC"完成任务\ntalk %x# welcome.4\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_30,14) && !who->get_legend(TASK_30,15) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    我那守卫可是向朱三要来的，你杀了他的手下，你有难了！哈哈哈，将军古墓四层东北将成为你的埋骨之处。\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( who->get_legend(TASK_30,15) && !who->get_legend(TASK_30,16) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    哈哈……敢去找我大哥麻烦，自讨苦吃！\n"ESC"离开", me->get_name()));
        	else if ( who->get_legend(TASK_30,16) && !who->get_legend(TASK_30,17) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你怎么还能活着！\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_30,17) && !who->get_legend(TASK_30,18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你告诉李屠那小子，回来修他的屋檐和半边墙吧，我没有搭理他了。\n"ESC"接受任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(),getoid(me)));
 
        	break;
        case 2:
        	if ( who->get_legend(TASK_30,10) && !who->get_legend(TASK_30,11) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_30,11);
			who->add_exp(65000);
			who->add_potential(780);
			who->add_cash(51000);
			send_user(who,"%c%s",';',"明辨是非 经验 65000 潜能 780 金钱 51000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,36,"" );
			me->do_welcome(1);
        	}
        	break;
        case 3:
        	if ( who->get_legend(TASK_30,11) && !who->get_legend(TASK_30,12) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_30,12);
        		who->delete_save("lbtqianyong");
        		who->delete_save("lbtgongjsy");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"齐国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,37,"威慑对手" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"威慑对手");
        	}
        	break; 
        case 4:
        	if ( who->get_legend(TASK_30,13) && !who->get_legend(TASK_30,14) )
        	{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_30,14);
        		who->delete_save("lbtqianyong");
        		who->delete_save("lbtgongjsy");			
			who->add_exp(67000);
			who->add_potential(790);
			who->add_cash(53000);
			send_user(who,"%c%s",';',"威慑对手 经验 67000 潜能 790 金钱 53000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,37,"" );
			me->do_welcome(1);
        	}
        	break;   
        case 5:
        	if ( who->get_legend(TASK_30,14) && !who->get_legend(TASK_30,15) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_30,15);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"齐国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,38,"铲除祸害" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"铲除祸害");
        	}
        	break; 
        case 6:
        	if ( who->get_legend(TASK_30,16) && !who->get_legend(TASK_30,17) )
        	{
        		if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
			TASK_LEGEND_D->give_item(who,"item/product/64157",1);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_30,17);
			who->add_exp(66000);
			who->add_potential(790);
			who->add_cash(52000);
			send_user(who,"%c%s",';',"铲除祸害 经验 66000 潜能 790 金钱 52000 荧光鞋图纸 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,38,"" );
			me->do_welcome(1);
        	}
        	break;   
        case 7:
        	if ( who->get_legend(TASK_30,17) && !who->get_legend(TASK_30,18) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_30,18);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_QIGUO,"齐国" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_QIGUO,39,"驯服恶霸" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"驯服恶霸");
        	}
        	break; 
        }
}