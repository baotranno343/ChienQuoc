
// 自动生成：/make/npc/make0002

#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>

inherit OFFICER;

// 函数：小贩识别
int is_seller() { return 3; }

// 函数：获取人物造型
int get_char_picid() { return 5404; }

// 有自己的do_look函数
int is_self_look() { return 1; }

void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Chủ Tiệm Vũ Khí");
        set_city_name("Tân Thủ Thôn");

        set_2( "good", ([
                "01" : "/item/70/0002",
                "02" : "/item/72/0002",
                "03" : "/item/74/0002",
                "04" : "/item/76/0002",
                "05" : "/item/75/0002",                                           

        ]) );
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ]));        
//        set("level", 0);
//        set("legend", ({ 4, 32+3 }));      
//	set("mpLegend",([0:({32+3,32*2+4 }),]));
	set("mpLegend2",([0:({32*48+3}),]));

        setup();
}

// 函数：对话处理
void do_look( object who )
{
	object me = this_object();
	string result;
	result = sprintf(" %s :\n "+"/quest/word"->get_normal_word(me)+"\n", me->get_name() );
	result += sprintf(ESC "Nơi nào có binh khí phù hợp với ta?\ntalk %x# welcome.99\n", getoid(me) ) ;        	
	"/quest/help"->send_help_tips(who, 39);
	if (who->get_legend(TASK_48, 2) && !who->get_legend(TASK_48, 3))
	{
		result = result + sprintf( ESC  +HIY+ "Thủ Thuật Nhỏ\ntalk %x# welcome.1\n", getoid(me) );
	}
//	if (who->get_legend(TASK_NEWBIE_00, 3) && !who->get_legend(TASK_NEWBIE_00, 4))
//	{
//		result = result + sprintf( ESC "索取木剑\ntalk %x# welcome.1\n", getoid(me) );
//	}
	if (who->get_legend(TASK_48, 3) && !who->get_legend(TASK_48, 4))
	{
		result = result + sprintf( ESC  +HIY+ "Thủ Tục Hợp Tác\ntalk %x# welcome.3\n", getoid(me) );
	}
//	if ( !who->get_legend(TASK_NEWBIE_02,4) || !who->get_legend(TASK_NEWBIE_02,5)||!who->get_legend(TASK_NEWBIE_02,6) )
//	{
//		result = result + sprintf( ESC "讨厌的山鸡\ntalk %x# welcome.5\n", getoid(me) );
//	}
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
		if (who->get_legend(TASK_48, 2) && !who->get_legend(TASK_48, 3))
//        	if (who->get_legend(TASK_NEWBIE_00, 3) && !who->get_legend(TASK_NEWBIE_00, 4))
        	{
	                cmd1 = sprintf("talk %x# welcome.2\n", getoid(me));
	                result =  get_name() + " :\n Còn trẻ tuổi thân thủ giỏi như vậy, lớn lên nhất định là người làm việc lớn!\n"
	                		ESC "Nhiệm vụ hoàn thành\n" + cmd1;
	                send_user( who, "%c%c%w%s", ':', 3, 5404, result );  
		}	                
                break;                
	case 2:       
		if (who->get_legend(TASK_48, 2) && !who->get_legend(TASK_48, 3))
//		if (who->get_legend(TASK_NEWBIE_00, 3) && !who->get_legend(TASK_NEWBIE_00, 4))
		{
                        item = new ("/item/32/3282");    // 桔子
                        if (item)
                        {
                                if( USER_INVENTORY_D->can_carry(who, item)  >=1 )
                                {
                                        p =item->move(who, -1);
                                        item->add_to_user(p);
                                        item->set_amount(5);
		                        send_user( who, "%c%s", '!', "得到"HIR"桔子"NOR"5个");		                                                                 
                                }       
                                else
                                {
                                	destruct(item); 
                                	send_user( who, "%c%s", '!', "您身上没有空位！");
                                	return;
                                }
                        }                                			
                        who->add_exp(100);
                        who->add_cash(800);
                        who->add_potential(30);
                        TASK_LEGEND_D->task_finish(who);
                        who->set_legend(TASK_48, 3);
			result = "Ngươi nhận được phần thưởng của Chủ Tiệm Vũ Khí 100 điểm Kinh nghiệm, 30 điểm Tiềm năng, 800 Ngân lượng, 5 Trái Quýt";
//                        who->set_legend(TASK_NEWBIE_00, 2);
                        send_user( who, "%c%s", ';', result);
			send_user( who, "%c%c%c%w%c", 0x51, 2, 1,TID_NEWBIE_01,0 );
			send_user( who, "%c%c%c%w%w%c", 0x51, 2, 2,TID_NEWBIE_01,101,0 );
                        "/sys/sys/count"->add_task("Thủ Thuật Nhỏ", 1);
		}      
//		me->do_look(who);
		me->do_welcome(3);
		break;  
	case 3:
		if (who->get_legend(TASK_48, 3) && !who->get_legend(TASK_48, 4))
			send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf("%s :\n Dụng cụ phòng ngự và binh khí vốn là một nhà, người nào có việc tốt thì chúng tách ra, thông báo cục diện phân tách. Nói thật lòng, ta  trước đây đã muốn thương lượng với Chủ Tiệm Giáp Trụ, chúng ta cùng hợp tác, mở một tiệm thương phẩm lớn hơn và đủ tất cả các lọai, trông thấy thôn ngày càng có nhiều người, thời cơ đã đến. Nên mời ngươi làm thuyết khách của ta, đến Chủ Tiệm Giáp Trụ một chuyến! cứ đi thẳng con đường này, sẽ tìm ra ngay Tiệm Giáp Trụ.\n"ESC"Nhận nhiệm vụ\ntalk %x# welcome.4\n"ESC"Rời khỏi",me->get_name(),getoid(me)));
//		else if ( !who->get_legend(TASK_NEWBIE_01, 4) )
//			send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf("%s:\n    难道那防具店老板不答应？这可是有利于大家的好事呀！\n"ESC"离开",me->get_name(),getoid(me)));
		break;
	case 4:
		if (who->get_legend(TASK_48, 3) && !who->get_legend(TASK_48, 4))
		{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			who->set_legend(TASK_48, 4);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"Tân Thủ Thôn" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,102,"Thủ Tục Hợp Tác" );
			send_user( who, "%c%s", '!', "Nhận nhiệm vụ "HIY"Thủ Tục Hợp Tác"NOR".");
		}
		break;
	case 5:
		if ( !who->get_legend(TASK_NEWBIE_02,4) )
			send_user( who, "%c%c%w%s", ':', 3, 5404, sprintf("%s:\n    村外的那些山鸡太可恶了，昨天居然跑到我店里偷吃！你去帮我杀死那帮盗贼吧！顺着这条路一直走，只要出了这个村子，你就能见到他们了！只要你帮我消灭掉他们，回到我这儿后，我会给你一些补偿的！\n"ESC"接受\ntalk %x# welcome.6\n"ESC"离开",me->get_name(),getoid(me)) );  
		else if ( !who->get_legend(TASK_NEWBIE_02,5) )
			send_user( who, "%c%c%w%s", ':', 3, 5404, sprintf("%s:\n    那帮可恶的山鸡昨天又来捣乱了，你还没有找到他们吗？就在村子外面呀！\n"ESC"离开",me->get_name()) );  
		else if ( !who->get_legend(TASK_NEWBIE_02,6) )
			send_user( who, "%c%c%w%s", ':', 3, 5404, sprintf("%s:\n    你已经一举剿灭他们了？真是太好了，可以过几天安心日子了，我该怎么报答你！小小礼物，不成敬意！\n"ESC"奖励长木剑\ntalk %x# welcome.7\n"ESC"奖励布拳套\ntalk %x# welcome.8\n"ESC"离开",me->get_name(),getoid(me),getoid(me)) );  
		break;
	case 6:
		if ( who->get_legend(TASK_NEWBIE_02,4) )
			return ;
		who->set_legend(TASK_NEWBIE_02,4);
		who->delete_save_2("newbie_sanji");
		send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"新手村" );
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,15,"讨厌的山鸡" );
		send_user( who, "%c%s", '!', "你接受了"HIY"讨厌的山鸡"NOR"任务");
		break;
	case 7:
	case 8:
		if ( !who->get_legend(TASK_NEWBIE_02,4) || !who->get_legend(TASK_NEWBIE_02,5) || who->get_legend(TASK_NEWBIE_02,6) )
			return ;
		if ( flag == 7 )
			item = new("item/76/0001");
		else
			item = new("item/70/0001");
		if ( !item )
			return;
		p = item->move(who,-1);
		if ( !p )
		{
			send_user(who,"%c%s",'!',"你身上的东西太多了");
			return;
		}
		item->add_to_user(p);
		who->add_exp(110);
		who->add_potential(10);
		who->add_cash(600);
		who->delete_save_2("newbie_sanji");
		who->set_legend(TASK_NEWBIE_02,6);
		send_user(who,"%c%s",';',"讨厌的山鸡 经验 110 潜能10 金钱 600 "+ item->get_name() + " 1");
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,15,"" );			
		break;

	case 99:
		result = sprintf(" %s :\n Không biết mua trang bị phù hợp ở nơi nào ư? Ta nói với ngươi rồi.\n"
			" Ở Tân Thủ Thôn và Sở Quốc ngươi có thể mua được trang bị thông dụng. Tân Thủ Thôn bán trang bị cấp 0, và Sở Quốc bán Trang bị cấp 10.\n"
			"    在"HIR" Triệu Quốc "NOR"可以买到"HIR" Đào Hoa Nguyên "NOR"的武器；\n"
			"    "HIR" Chu Quốc "NOR"有"HIR" Cấm Vệ Quân "NOR"武器的专门店；\n"
			"    "HIR" 蜀山 "NOR"的武器可以在"HIR" Yên Quốc "NOR"购买；\n"
			"    到"HIR" Hàn Quốc "NOR"就可以找到"HIR" 唐门 "NOR"的武器专门店；\n"
			"    在"HIR" Tần Quốc "NOR"能买到"HIR" 昆仑山 "NOR"的法器；\n"
			"    "HIR" 茅山 "NOR"的法器可以到"HIR" Tề Quốc "NOR"寻寻看；\n"
			"    最后"HIR" 云梦泽 "NOR"的法器你只要到"HIR" Ngụy Quốc "NOR"便可以找到了。"
			"\n", me->get_name() );
		send_user( who, "%c%c%w%s", ':', 3, me->get_char_picid(), result );
		break;
	}
}	               
