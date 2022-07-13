
// 自动生成：/make/npc/make0002

#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>

inherit OFFICER;

// 函数：小贩识别
int is_seller() { return 5; }
// 有自己的do_look函数
int is_self_look() { return 1; }
// 函数：获取人物造型
int get_char_picid() { return 5402; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Chủ Tiệm Tạp Hóa");
        set_city_name("Tân Thủ Thôn");

        set_2( "good", ([
                "01" : "/item/std/0401",
                "02" : "/item/std/0407",
                "04" : "/item/std/0409",
                "05" : "/item/std/0413",
                "06" : "/item/std/0591",
                "07" : "/item/32/3231",
                "08" : "/item/98/9871",
                "09" : "/item/std/9808",
		"10" : "/item/std/9819",
		"11" : "/item/std/9820",
		"12" : "/item/49/4900",
		"13" : "/item/std/0410",
		"14" : "/item/08/0010",
		"15" : "/item/08/0011",
		"16" : "/item/08/0012",
		"17" : "/item/44/4403",
		"18" : "/item/44/4406",
//		"19" : "/item/44/4405",
        ]) );
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));
//        set("level", 0);
//        set("legend", ({ 32*41+11 }));
	set("mpLegend",([5:({32*49+15}),]));
	set("mpLegend2",([0:({32*48+14,32*49+17}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	object me = this_object();
	string result="";
	"/quest/help"->send_help_tips(who, 41);
	result = sprintf(" %s :\n "+"/quest/word"->get_normal_word(me)+"\n", me->get_name() );
	if ( who->get_legend(TASK_48, 13) && !who->get_legend(TASK_48, 14) )
	{
		result = result + sprintf( ESC +HIY+  "Bồ Câu Đưa Thư\ntalk %x# welcome.1\n", getoid(me) );
	}
//	if ( !who->get_legend(TASK_NEWBIE_01, 14) )
	if ( who->get_legend(TASK_48, 14) && !who->get_legend(TASK_48, 15) )
	{
		result = result + sprintf( ESC  +HIY+ "修理店老板的铁锤\ntalk %x# welcome.3\n", getoid(me) );
	}	
	if ( who->get_legend(TASK_NEWBIE_01, 14) && !who->get_legend(TASK_NEWBIE_01, 15) )
	{
		result = result + sprintf( ESC  +HIY+ "修理店老板的铁锤\ntalk %x# welcome.5\n", getoid(me) );
	}
	if ( who->get_level() >=5 && !who->get_legend(TASK_49, 17) )
	{
		result = result + sprintf( ESC +HIY+ "蚂蚁带来的烦恼\ntalk %x# welcome.8\n", getoid(me) );
	}
/*	if ( who->get_level() >=5 && !who->get_legend(TASK_41, 11) )
	{
		result = result + sprintf( ESC "运箱子\ntalk %x# welcome.6\n", getoid(me) );
	}*/

	result = result + sprintf( ESC "Giao dịch\nlist %x#\n" ESC "Ta chỉ tiện xem qua\nCLOSE\n", getoid(me) ) ;        	
	send_user( who, "%c%s", ':', result );

}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        int flag, date , status, p, z, x, y, i;
        object who, obj, item;     
        string cmd1, cmd2, cmd3, cmd4, cmd5, result;
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
	case 1:
//		if ( !who->get_legend(TASK_NEWBIE_01, 12)||who->get_legend(TASK_NEWBIE_01, 13) )
//			return;
		if ( who->get_legend(TASK_48, 13) && !who->get_legend(TASK_48, 14) )
		send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf("%s:\n    咳…咳…咳…信送来了？我每天都等着这份出货单，好给他发货，知道是谁送来的吗？是我的兄弟，他在周国，以后你会有机会见到他的！过来拿你的报酬吧，孩子。\n"ESC"完成任务\ntalk %x# welcome.2\n"ESC"离开",me->get_name(),getoid(me)));
		break;
	case 2:
//		if ( !who->get_legend(TASK_NEWBIE_01, 12)||who->get_legend(TASK_NEWBIE_01, 13) )
//			return;
		if ( who->get_legend(TASK_48, 13) && !who->get_legend(TASK_48, 14) )
		{
			if( !objectp( item = present("Giấy Xuất Hàng", who, 1, MAX_CARRY) ) || item->is_huodan() != 1 )
			{
				send_user(who,"%c%s",'!',"你的出货单呢?");
				return;			
			}	
			item->remove_from_user();
			destruct(item);			
			item = new("/item/08/0010");
			p =item->move(who, -1);
                        item->add_to_user(p);	
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_48, 14);	
			who->add_exp(290);
			who->add_potential(20);
			who->add_cash(200);
			send_user(who,"%c%s",';',"飞鸽传书 经验 290 潜能 20 金钱 200 普通鉴定镜 1");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,106,"" );
			me->do_welcome(3);
		}
		break;
	case 3:
//		if ( who->get_legend(TASK_NEWBIE_01, 14) )
//			return;		
		if ( who->get_legend(TASK_48, 14) && !who->get_legend(TASK_48, 15) )
		send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf("%s:\n    前些日子修理店老板来我这想买一把铁锤，可惜我这里没有，但是我答应他，给他找到铁锤，据我打听得来的消息，在清溪有两种叫做小蚂蚁与小蜜蜂的动物，他们身上带着铁锤，可能对于你来说，他们的力量有点强大，所以你一定要小心哦。当然，比较困难的事情我一般会给比较高的报酬哦。你拿到铁锤后直接交给修理店老板就行了。\n    做完任务后，用alt+w打开人物属性界面，再使用新手信物就可以快速回到新手村哦！\n"ESC"接受任务\ntalk %x# welcome.4\n"ESC"离开",me->get_name(),getoid(me)));
		break;
	case 4:
//		if ( who->get_legend(TASK_NEWBIE_01, 14) )
//			return;
		if ( who->get_legend(TASK_48, 14) && !who->get_legend(TASK_48, 15) )
		{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			who->set_legend(TASK_48, 15);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"新手村" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,107,"修理店老板的铁锤" );
			send_user( who, "%c%s", '!', "你接受了"HIY"修理店老板的铁锤"NOR"任务");
		}
		break;	
	case 5:
		if ( who->get_legend(TASK_NEWBIE_01, 14) && !who->get_legend(TASK_NEWBIE_01, 15) )
			send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf("%s:\n    是他们太强了吗？你可得赶快哦，我答应了修理店老板，可不想失信于他。\n"ESC"离开",me->get_name(),));
		break;
        case 6:
        	if ( who->get_level() >=5 && !who->get_legend(TASK_41,11) )
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s:\n    村外的刘大叔托我买的东西，我已经全部收集齐了，把它们全放在这个箱子里了，你能给我运过去吗？\n    刘大叔就住在往巴丘去的大路旁边，和李老汉是很好的邻居呢，如果你以前往那个方向走过，你应该很容易就找到他的，不过没去过也不要紧，你往那条路上走，见到两个独门独户的房子，就是刘大叔家了。\n"ESC"接受任务\ntalk %x# welcome.7\n"ESC"离开", me->get_name(), getoid(me)));
        	break;
	case 7:
        	if ( who->get_level() >=5 && !who->get_legend(TASK_41,11) )
        	{
			if ( TASK_LEGEND_D->can_carry_amount(who,1) != 1 )
        			return ;
			TASK_LEGEND_D->give_item(who,"item/98/0201",1);
        		who->set_legend(TASK_41,11);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"新手村" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,33,"运箱子" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"运箱子");
        	}
        	break;			
        case 8:
		if( who->get_level() >=5 && !who->get_legend(TASK_49, 15) )
        		send_user(who,"%c%s",':',sprintf("%s\n    我从小就爱吃蜂蜜，一吃起来就没个够，现在年纪虽然不小了，口味却一直没变。前些天我一位老朋友从巴丘过来，给我带来了十罐蜂蜜，我把它们收藏在幽谷的木屋里。不过幽谷那里有很多小蚂蚁活动，我一直很担心它们会去偷吃我的蜂蜜，你要是有空去帮我干掉几只小蚂蚁，那样我就能安心了。\n"ESC"接受任务\ntalk %x# welcome.9\n"ESC"离开",me->get_name(),getoid(me)));
		else if ( who->get_legend(TASK_49, 16) && !who->get_legend(TASK_49, 17) )
        		send_user(who,"%c%s",':',sprintf("%s\n    你已经干掉小蚂蚁了？太好了，我终于放心了，这些钱是我谢谢你的，省着点，别一次花完了。\n"ESC"完成任务\ntalk %x# welcome.10\n"ESC"离开",me->get_name(),getoid(me)));
        	break;
	case 9:
		if ( who->get_level() >=5 && !who->get_legend(TASK_49, 15) )
		{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			who->set_legend(TASK_49, 15);
			who->delete_save("xsc_mayi");
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"新手村" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,45,"蚂蚁带来的烦恼" );
			send_user( who, "%c%s", '!', "得到任务 "HIY"蚂蚁带来的烦恼");	
		}
		break;
	case 10:
		if ( who->get_legend(TASK_49, 16) && !who->get_legend(TASK_49, 17) )
		{
			TASK_LEGEND_D->task_finish(who);
			who->delete_save_2("xsc_mayi");
			who->add_exp(150);
			who->add_potential(25);
			who->add_cash(800);
			who->set_legend(TASK_49, 17);
			send_user(who,"%c%s",';',"蚂蚁带来的烦恼 经验 150 潜能 25 金钱 800");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,45,"" );			
		}
		break;
	}
}
