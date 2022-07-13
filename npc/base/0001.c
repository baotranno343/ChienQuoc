
// 自动生成：/make/npc/make0001

#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>

inherit OFFICER;

// 函数：当铺老板
int is_banker() { return 1; }
void do_welcome(string arg);

// 函数：获取人物造型
int get_char_picid() { return 5301; }

// 函数：构造处理
void create()
{
        set_name("Quản Khố");
        set_real_name("Quản Khố");
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
//        set("level",0);
//        set("legend",({32*40+17}));
//	set("mpLegend",([0:({32*2+1,32*40+17}),5:({32*40+24})]));
	set("mpLegend",([0:({32*40+17})]));
	set("mpLegend2",([0:({32*48+30,32*49+5,32*40+19}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp="";
	
	if ( !who->get_legend(TASK_40,19) )
		tmp +=  sprintf(ESC +HIY+  "锻炼自己\ntalk %x# welcome.4\n",getoid(this_object()));
	if ( who->get_legend(TASK_48, 29) && !who->get_legend(TASK_48, 30))
		tmp +=  sprintf(ESC +HIY+  "Trang Trí Phòng Ốc\ntalk %x# welcome.10\n",getoid(this_object()));
//	if ( !who->get_legend(TASK_NEWBIE_02,3) )
	if ( who->get_legend(TASK_49, 5) && !who->get_legend(TASK_49, 6))
		tmp +=  sprintf(ESC  +HIY+ "Giao Dịch Của Chủ Tiệm Cầm Đồ\ntalk %x# welcome.1\n",getoid(this_object()));
       	if ( who->get_legend(TASK_48, 30) && !who->get_legend(TASK_49, 1))
//	if ( (who->get_level() >= 5 &&!who->get_legend(TASK_40,24)) || (who->get_legend(TASK_40,28) && !who->get_legend(TASK_40,29)) )
		tmp +=  sprintf(ESC  +HIY+ "Chứng Bệnh Đau Đầu\ntalk %x# welcome.7\n",getoid(this_object()));
       	if ( who->get_legend(TASK_49, 4) && !who->get_legend(TASK_49, 5))
		tmp +=  sprintf(ESC  +HIY+ "Chứng Bệnh Đau Đầu(3)\ntalk %x# welcome.7\n",getoid(this_object()));
	tmp += sprintf(ESC "Nhận lãnh Chiến Quốc Bảo Điển\ntalk %x# welcome.12\n",getoid(this_object()));
        send_user( who, "%c%c%w%s", ':', 3, get_char_picid(), 
                sprintf(" %s :\n "+"/quest/word"->get_normal_word(this_object())+"\n"
                        ESC "Ta muốn sử dụng kho\npawn %x# 1\n"
			ESC "Ta muốn mở rộng kho của ta\npawn expand %x# 0\n"
                        + tmp +
                        ESC "Ta chỉ xem qua\nCLOSE\n",get_name(), getoid(this_object()), getoid(this_object()) ) );
	"/quest/help"->send_help_tips(who, 4);                        
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
	int flag,i,size,p,amount;
	object who,*inv,item;
	
	who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {	
		case 1:
//			if (!who->get_legend(TASK_NEWBIE_02,1) )
			if ( who->get_legend(TASK_49, 5) && !who->get_legend(TASK_49, 6))
				send_user( who, "%c%c%w%s", ':', 3, me->get_char_picid(),
					sprintf("%s:\n    嘿，看来你需要一些行军散，这可是对你的气血非常有用的。对吗？\n    我很愿意给你一些行军散，但是，我有一个条件，门派向导一直想找点火焰石玩玩，我想讨好他，所以你帮他弄一些火焰石来，你看怎么样？\n    你去洞庭湖杀掉那些讨厌的持扇草人、赤褐蚁或子母蛙，就可能会有火焰石了，拿到后交给门派向导，他只需要5个，去吧！\n    做完任务后，用alt+w打开人物属性界面，再使用新手信物就可以快速回到新手村哦！\n"ESC"接受\ntalk %x# welcome.2\n"ESC"离开",me->get_name(),getoid(me)));
			else if (!who->get_legend(TASK_NEWBIE_02,2) )
				send_user( who, "%c%c%w%s", ':', 3, me->get_char_picid(),
					sprintf("%s:\n   %s ，我交给你的任务呢？完成了吗？我还等着你呢！村外就有很多野兔，你杀死它们就可以拿到火焰石了！”\n"ESC"离开",me->get_name(),NPC_RANK_D->get_respect_2(who)));
			else if (!who->get_legend(TASK_NEWBIE_02,3) )
				send_user( who, "%c%c%w%s", ':', 3, me->get_char_picid(),
					sprintf("%s:\n    没想到你这么快就回来了，%s。青出于蓝而胜于蓝啊！我这把老骨头了，一个人也挺寂寞的，谢谢你找来这些火焰石供我把玩。这是给你的奖励！\n"ESC"完成任务\ntalk %x# welcome.3\n"ESC"离开",me->get_name(),NPC_RANK_D->get_respect_2(who),getoid(me)));
			break;
		case 2:
//			if ( who->get_legend(TASK_NEWBIE_02,1) )
//				return ;
			if ( who->get_legend(TASK_49, 5) && !who->get_legend(TASK_49, 6))
			{
				if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
				who->set_legend(TASK_49,6);
				who->delete_save_2("huoyanshi");
				send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"Tân Thủ Thôn" );
				send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,116,"当铺老板的交易" );
				send_user( who, "%c%s", '!', "你接受了"HIY"当铺老板的交易"NOR"任务");
			}
			break;
		case 3:
			if ( !who->get_legend(TASK_NEWBIE_02,1) || !who->get_legend(TASK_NEWBIE_02,2) || who->get_legend(TASK_NEWBIE_02,3) )
				return ;	
			if( !objectp( item = present("火焰石", who, 1, MAX_CARRY) ) || item->is_huoyanshi() != 1 )
			{
				send_user(who,"%c%s",'!',"你的火焰石呢?");
				return;	
			}
			inv = all_inventory(who, 1, MAX_CARRY);
               		inv -= ({ 0});
               		for( i = 0, size = sizeof(inv); i < size; i ++ )
               		{
                		if ( !objectp(inv[i]) )
                			continue;
                		if ( inv[i]->get_name() != "火焰石" || inv[i]->is_huoyanshi() != 1 )
                			continue;
                		amount += inv[i]->get_amount();               			
               		}
               		if ( amount < 5 )
               		{
               			send_user(who,"%c%s",'!',"数量不够吧?");
				return;
               		}
                	for( i = 0, size = sizeof(inv); i < size; i ++ )
                	{
                		if ( !objectp(inv[i]) )
                			continue;
                		if ( inv[i]->get_name() != "火焰石" || inv[i]->is_huoyanshi() != 1 )
                			continue;
                		inv[i]->remove_from_user();
                		destruct(inv[i]);
                	}
                	item = new("/item/91/9100");
                	if ( !item )
                		return ;
                	item->set_amount(10);
                	p = item->move(who,-1);
                	if ( !p )
                	{
                		send_user(who,"%c%s",'!',"你身上的东西太多了");
                		return;
                	}
                	item->add_to_user(p);
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_NEWBIE_02,3);
			who->delete_save_2("huoyanshi");
			who->add_exp(100);
			send_user(who,"%c%s",';',"当铺老板的交易 经验 100 行军散 10");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,14,"" );
			break;
        case 4:
        	if ( !who->get_legend(TASK_40,17) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    看上去你很少参加战斗，%s，我猜想你肯定还没有去过村外，也没有见过那些恼人的小山鸡、小野兔、稻草人，我觉得，你应该出村锻炼下自己，不止能让你自身的能力得到提高，还能让人见到一些你从未见过的东西，开阔你的视野。\n    我看不如这样吧，你去村外消灭3只小怪物（小山鸡、小野兔、稻草人），回来向我交差，我会给奖励给你的！\n"ESC"接受任务\ntalk %x# welcome.5\n"ESC"离开", me->get_name(), who->get_name(),getoid(me)));
		else if ( !who->get_legend(TASK_40,18) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    你应该出村锻炼下自己。\n"ESC"离开", me->get_name(),getoid(me)));
        	else if ( !who->get_legend(TASK_40,19) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    真不错！没想到你能这么快就回来。拿好你的奖励，孩子。\n"ESC"完成任务\ntalk %x# welcome.6\n"ESC"离开", me->get_name(),getoid(me)));
        	
        	break;
	case 5:
        	if ( !who->get_legend(TASK_40,17) )
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_40,17);
        		who->delete_save("dplbxiaogw");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"Tân Thủ Thôn" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,32,"锻炼自己" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"锻炼自己");
        	}
        	break;
        case 6:
        	if ( who->get_legend(TASK_40,18) && !who->get_legend(TASK_40,19) )
        	{
        		TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_40,19);
        		who->delete_save("dplbxiaoyt");
        		who->delete_save("dplbdaocr");
			who->add_exp(280);
			who->add_potential(15);
			who->add_cash(500);
			send_user(who,"%c%s",';',"锻炼自己 经验 280 潜能 15 金钱 500");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,32,"" );
        	}
        	break;   
        case 7:
//        	if ( who->get_level() >= 5 &&!who->get_legend(TASK_40,24) )
	       	if ( who->get_legend(TASK_48, 30) && !who->get_legend(TASK_49, 1))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    为了这个当铺，我是日夜操劳，白天忙着为客人服务，晚上又得清算盘点，久而久之，便有了头疼的毛病，每当遇到烦恼的事情时，脑袋里就撕裂般的疼痛，有时候实在是疼得受不了，我便拿自己的头往墙壁上撞。\n    我听说灵芝草对头疼有很强的疗效，我想请你去找野味收购商讨点灵芝草来，他收购野味应该也会收购一些药材，如果他有其他条件，你尽管答应好了，我会想办法让你做到的。\n"ESC"接受任务\ntalk %x# welcome.8\n"ESC"离开", me->get_name(), getoid(me)));
//        	else if ( who->get_legend(TASK_40,28) && !who->get_legend(TASK_40,29) )
	       	else if ( who->get_legend(TASK_49, 4) && !who->get_legend(TASK_49, 5))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    果然不负我所望，将灵芝草给我讨了来，我这头疼的毛病就全靠你这颗灵芝草了，我要好好答谢你！\n"ESC"完成任务\ntalk %x# welcome.9\n"ESC"离开", me->get_name(),getoid(me)));
       	
        	break;
	case 8:
//        	if ( who->get_level() >= 5 &&!who->get_legend(TASK_40,24) )
	       	if ( who->get_legend(TASK_48, 30) && !who->get_legend(TASK_49, 1))
        	{
        		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
        		who->set_legend(TASK_49,1);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"Tân Thủ Thôn" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,113,"头疼的毛病（1）" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"头疼的毛病（1）");
        	}
        	break;
	case 9:
//		if( who->get_legend(TASK_40,28) && !who->get_legend(TASK_40,29) )
		if ( who->get_legend(TASK_49, 4) && !who->get_legend(TASK_49, 5))
		{
			if (TASK_LEGEND_D->check_task_item(who,"灵芝草",1) != 1 )
        			return;
			if(who->get_gender()==1) item = new("item/65/0001");
				else item = new("item/66/0001");
			p =item->move(who, -1);
			item->add_to_user(p);
			who->add_exp(280);
			who->add_potential(40);
			who->add_cash(1000);
			who->set_legend(TASK_49, 5);
			send_user(who,"%c%s",';',"头疼的毛病（3） 经验 280 潜能 40 金钱 1000 新手帽子 1");			
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,115,"" );
			me->do_welcome(1);
		}
		break;	
        case 10:
		if ( who->get_legend(TASK_48, 29) && !who->get_legend(TASK_48, 30))
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    不错，就是这种百合花，是我最喜欢的！\n"ESC"完成任务\ntalk %x# welcome.11\n"ESC"离开", me->get_name(),getoid(me)));
        	break;
        case 11:
        	if ( who->get_legend(TASK_48, 29) && !who->get_legend(TASK_48, 30))
        	{
        		if (TASK_LEGEND_D->check_task_item(who,"百合花",3) != 1 )
        			return;
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_48,30);
        		who->delete_save("wdzbaihh");
			who->add_exp(550);
			who->add_potential(30);
			who->add_cash(1000);
			send_user(who,"%c%s",';',"装饰房屋 经验 550 潜能 30 金钱 1000");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,112,"" );
			me->do_welcome(7);
        	}
        	break; 
        case 12:
		if(objectp(item = "/quest/zg_dict"->want_an_zgdict(me,who))) {
			p = item->move(who,-1);
			item->add_to_user(p);
			send_user(who,"%c%s",'!',"Ngươi đạt được Chiến Quốc Bảo Điển");
		}        	
        	break;
	}
}
