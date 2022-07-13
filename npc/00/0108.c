
#include <npc.h>
#include <ansi.h>
#include <task.h>

inherit OFFICER;

void do_visit(string arg);
void do_welcome( string arg );

// 函数：获取人物造型
int get_char_picid() { return 6001; }

// 函数：构造处理
void create()
{
        set_name( "Lão Thôn Trưởng" );

        set_2( "talk", ([
                "visit"		: (: do_visit :),
                "welcome"    : (: do_welcome :),
        ]));      
//        set("level", 7);
//        set("legend", ({ 32*2+14 }));        
	set("mpLegend",([5:({32*2+24,}),]));

	
        setup();
        if( !clonep(this_object()) ) return;
	"npc/task/0100"->create_npc();
}

// 函数：对话处理
void do_look( object who )
{
        object me = this_object();
        int id = getoid(me),i;
        string tmp="";
        
	if ( who->get_legend(TASK_NEWBIE_01, 1) && !who->get_legend(TASK_NEWBIE_01, 2) )
		tmp += sprintf(ESC"门派向导的介绍。\ntalk %x# visit.1\n",getoid(me));
	if( who->get_level() >= 5 && !who->get_legend(TASK_NEWBIE_02, 24) )
        {
		tmp += sprintf(ESC +HIY+ "美味的蜜糖\ntalk %x# visit.9\n",getoid(this_object()));
        }
/*	if ( (who->get_level() >= 5 && !who->get_legend(TASK_41, 4)) || (who->get_legend(TASK_41, 9) && !who->get_legend(TASK_41, 10)) )
		tmp += sprintf(ESC"疑难杂症\ntalk %x# visit.6\n",getoid(me));
	if ( who->get_level() >= 5 && !who->get_legend(TASK_NEWBIE_02, 16) )
		tmp += sprintf(ESC"惩治恶将\ntalk %x# visit.3\n",getoid(me));*/

	send_user( who, "%c%s", ':', me->get_name() + "：\n    最近村中的麻烦事越来越多了，看来单靠村卫团的力量还是不足啊……\n" +
                        tmp +
	                ESC "领取特别奖励须知\n" + sprintf( "talk %x# welcome.1021\n", id ) +
        	        ESC "领取师傅特别奖励\n" + sprintf( "talk %x# welcome.1030\n", id ) +
                        ESC "离开。\nCLOSE\n" );
}


void do_visit(string arg) { __FILE__->do_visit_call(this_player(),this_object(),arg);}

void do_visit_call(object who, object npc, string arg)
{
	int i,p;
	object item,item1;
	
	i = to_int(arg);
	if ( i < 3 && who->get_legend(TASK_NEWBIE_01, 1) && !who->get_legend(TASK_NEWBIE_01, 2) )
	{
		if ( i == 1 )
		{
			send_user( who, "%c%c%w%s", ':',3,npc->get_char_picid(), sprintf("%s:\n    村子里的人都是热心人，知道我最近为了这些事忙得焦头烂额的，发现了能帮上忙的人都往我这介绍，可我这的事情得需要一定的等级才能做哦，不然到时候出问题了，我只是个小小的村长，可负不起这个责啊。\n"ESC"完成任务\ntalk %x# visit.2\n",npc->get_name(),getoid(npc)));
		}
		else if ( i == 2 )
		{
			who->set_legend(TASK_NEWBIE_01, 2);
			who->add_exp(200);
			who->add_potential(10);
			send_user(who,"%c%s",';',sprintf("老村长的委托 经验 200 潜能 10"));
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,12,"" );
		}
		return ;
	}
	else if ( (i >= 3 && i <= 5) && who->get_level() >= 5  && !who->get_legend(TASK_NEWBIE_02, 16) )
	{
		if ( i == 3  )
		{
			if ( !who->get_legend(TASK_NEWBIE_02, 14) )
				send_user( who, "%c%c%w%s", ':',3,npc->get_char_picid(), sprintf("%s:\n    恶将胡仗着自己家有钱有势，勾结地方官府，欺压百姓，至今逍遥法外。你要替天行道，杀死恶将胡。\n    他就在清溪的清溪北野，最东边的地方。\n"ESC"接受任务\ntalk %x# visit.4\n"ESC"离开",npc->get_name(),getoid(npc)));
			else if ( !who->get_legend(TASK_NEWBIE_02, 15) )
				send_user( who, "%c%c%w%s", ':',3,npc->get_char_picid(), sprintf("%s:\n    你遇到困难了吗？还是那恶将胡又溜掉了？他可真狡猾，不过你还是去找找吧，想要做个为民除害的大英雄也不是那么容易的。\n"ESC"离开",npc->get_name(),getoid(npc)));
			else if ( !who->get_legend(TASK_NEWBIE_02, 16) )
				send_user( who, "%c%c%w%s", ':',3,npc->get_char_picid(), sprintf("%s:\n    这个大魔头终于得到了他应得的惩罚！你是个为民除害的大英雄呀！干得不错，孩子。要再接再厉！\n"ESC"完成任务\ntalk %x# visit.5\n"ESC"离开",npc->get_name(),getoid(npc)));

		}
		else if ( i == 4 && !who->get_legend(TASK_NEWBIE_02, 14) )
		{
			who->set_legend(TASK_NEWBIE_02, 14);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"新手村" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,20,"惩治恶将" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"惩治恶将");			
		}
		else if ( i == 5 && who->get_legend(TASK_NEWBIE_02, 15)&& !who->get_legend(TASK_NEWBIE_02, 16) )
		{
			item1 = new("item/80/0001");
			if ( !item1 )
				return;
			item = new("item/32/3282");
			if ( !item )
			{
				destruct(item1);
				return;
			}
			if( USER_INVENTORY_D->can_carry(who, item1)  < 2 )
			{
				notify( "你身上的东西太多了" );
				destruct(item);
				destruct(item1);
				return ;
			}
			ITEM_EQUIP_D->init_equip_prop_1(item1);	
			p = item1->move(who,-1);
			item1->add_to_user(p);
			item->set_amount(10);
			p = item->move(who,-1);
			item->add_to_user(p);
			who->set_legend(TASK_NEWBIE_02, 16);
			who->add_exp(550);
			who->add_potential(60);
			who->add_cash(2600);
			send_user(who,"%c%s",';',"惩治恶将 经验 550 潜能 60 金钱 2600 桔子 10 鹰目头巾 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,20,"" );			
		}
		return ;
	}
	switch(i)
        {
        case 6: 
		if ( who->get_level() >= 5 && !who->get_legend(TASK_41, 4) )
			send_user(who,"%c%s",':',sprintf("%s:\n    新手村的村民几乎都患上了一种病，他们全身疲软无力，成天想睡觉，没有精神去耕种，去开店做生意，严重影响了村民的正常生活，之前我已经询问过药店老板了，可惜他也不知道这是种什么病，他说他行医这么多年从未见过如此奇怪的病症，他说智慧老人见多识广，应该会知道，所以想请你去趟智慧老人家，询问他关于村人病症之事。\n    智慧老人就在往巴丘去的路边，你好好找找吧。找到他后注意问得详细点。\n"ESC"接受任务\ntalk %x# visit.7\n"ESC"离开",npc->get_name(),getoid(npc)));
		else if ( who->get_legend(TASK_41, 9) && !who->get_legend(TASK_41, 10) )
			send_user(who,"%c%s",':',sprintf("%s:\n    是的！我早就疑心是有人下毒了，我定会好好调查此事的，这一路上辛苦你了！\n"ESC"完成任务\ntalk %x# visit.8\n"ESC"离开",npc->get_name(),getoid(npc)));

        	break;
	case 7:
		if ( who->get_level() >= 5 && !who->get_legend(TASK_41, 4) )
        	{
        		who->set_legend(TASK_41,4);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"新手村" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,27,"疑难杂症（1）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"疑难杂症（1）");
        	}
        	break;        	
	case 8:
		if( who->get_legend(TASK_41, 9) && !who->get_legend(TASK_41, 10) )
		{
			if (TASK_LEGEND_D->check_task_item(who,"解药",1) != 1 )
        			return;
			TASK_LEGEND_D->give_item(who,"item/91/9100",5);
			who->add_exp(600);
			who->add_potential(70);
			who->add_cash(2000);
			who->set_legend(TASK_41, 10);
			send_user(who,"%c%s",';',"疑难杂症（3） 经验 600 潜能 70 金钱 2000 行军散 5");			
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,29,"" );
		}
		break;	        
	case 9:
		if( who->get_level() >= 5 && !who->get_legend(TASK_NEWBIE_02, 24) )
			send_user(who,"%c%s",':',sprintf("%s:\n    清溪的李小毛经常说这个世上最甜最美味的就是蜜糖。他真的很想尝尝，真是个可爱的小孩儿！\n    我知道清溪和幽谷附近的蜜蜂都会带着蜜糖在身上，你能帮这个可爱的小孩儿取3罐蜜糖吗？\n"ESC"接受任务\ntalk %x# visit.10\n"ESC"离开",npc->get_name(),getoid(npc)));
		
		break;
	case 10:
		if( who->get_level() >= 5 && !who->get_legend(TASK_NEWBIE_02, 24) )
		{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			who->set_legend(TASK_NEWBIE_02, 24);
			who->delete_save_2("xiaomao_fengmi");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_YEWAI,"清溪" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_YEWAI,1,"美味的蜜糖" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"美味的蜜糖");	
		}
		break;
        }
}

// 函数：移动处理
void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        object who;
        int p, z, x, y, flag;
	object item;
	
        who = this_player();
        
        flag = to_int(arg);
        switch(flag)
        {

	case 1021:
                send_user( who, "%c%s", ':', get_name() + "：\n    老夫对于辛勤培育徒弟的师傅非常赏识，因此特别为师傅方准备了一份奖励！当徒弟每到10级、20级、30级、40级时，师傅方可以来老夫这领取丰厚的经验奖励。不过，这经验必须用你和徒弟的友好度来换取，既然你辛勤培育过徒弟，想必友好度一定不会少吧～！呵呵……\n"ESC"离开");                
		break;
	case 1030:
		TEACHER_D->friend_bonus_list1(me,who);
		break;
	case 1031..1034:
		TEACHER_D->friend_bonus_list2(me,who,flag);
		break;
	case 1100..1500:
		TEACHER_D->get_friend_bonus(me,who,flag);
		break;
        }
}
