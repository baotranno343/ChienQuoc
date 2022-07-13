
// 自动生成：/make/npc/make0002

#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>

inherit OFFICER;

// 函数：小贩识别
int is_seller() { return 4; }
// 有自己的do_look函数
int is_self_look() { return 1; }
// 函数：获取人物造型
int get_char_picid() { return 5405; }
void do_welcome( string arg );

// 函数：构造处理
void create()
{
        set_name("Chủ Tiệm Giáp Trụ");
        set_city_name("Tân Thủ Thôn");

        set_2( "good", ([
                "01" : "/item/60/0005",
                "02" : "/item/61/0005",
                "03" : "/item/65/0005",
                "04" : "/item/66/0005",
                "05" : "/item/88/0005",
        ]) );
        set_2( "talk", ([
                "welcome"          : (: do_welcome :),
        ])); 
//        set("level", 0);
//        set("legend", ({ 32+5,32+7 }));
//	set("mpLegend",([0:({32+5, }),]));
	set("mpLegend2",([0:({32*48+5,32*48+7,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	object me = this_object();
	string result;
	"/quest/help"->send_help_tips(who, 40);
	result = sprintf(" %s :\n "+"/quest/word"->get_normal_word(me)+"\n", me->get_name() );
	result += sprintf(ESC "Nơi nào có trang bị thích hợp với ta?\ntalk %x# welcome.99\n", getoid(me) ) ;        	
	if (who->get_legend(TASK_48, 4) && !who->get_legend(TASK_48, 5))
	{
		result = result + sprintf( ESC  +HIY+ "Thủ Tục Hợp Tác\ntalk %x# welcome.1\n", getoid(me) );
	}
	if (who->get_legend(TASK_48, 5) && !who->get_legend(TASK_48, 6))
	{
		result = result + sprintf( ESC  +HIY+ "Việc trải qua đi tìm kho báu\ntalk %x# welcome.3\n", getoid(me) );
	}
	if (who->get_legend(TASK_48, 6) && !who->get_legend(TASK_48, 7))
	{
		result = result + sprintf( ESC  +HIY+ "Việc trải qua đi tìm kho báu\ntalk %x# welcome.9\n", getoid(me) );
	}
	if ( (who->get_legend(TASK_48, 7) && !who->get_legend(TASK_48, 8)) )
	{
		result = result + sprintf( ESC  +HIY+ "Gia Tộc Ngọc Bội\ntalk %x# welcome.6\n", getoid(me) );
	}
	if (who->get_legend(TASK_NEWBIE_01, 7) && !who->get_legend(TASK_NEWBIE_01, 8))
	{
		result = result + sprintf( ESC  +HIY+ "Gia Tộc Ngọc Bội\ntalk %x# welcome.8\n", getoid(me) );
	}	
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
		if ( who->get_legend(TASK_48, 4) && !who->get_legend(TASK_48, 5))
			send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf(" %s :\n Ái chà! Chủ Tiệm Vũ Khí với ta quả là rất hiểu nhau! Ta cũng đã nghĩ ra cách này rồi, cám ơn ngươi đến làm thuyết khách của ông ấy, thế này đi, ta sẽ hẹn một bữa Trò Chuyện với ông ấy, cầm lấy thù lao của ngươi đây!\n"ESC"Hoàn thành nhiệm vụ\ntalk %x# welcome.2\n",me->get_name(),getoid(me)));
		break;
	case 2:
		if ( who->get_legend(TASK_48, 4) && !who->get_legend(TASK_48, 5))
		{
			if(who->get_gender()==1) item = new("item/60/0001");
				else item = new("item/61/0001");
			if ( !item ) break;
			if( USER_INVENTORY_D->can_carry(who, item)  >=1 )
			{
                                p =item->move(who, -1);
                                item->add_to_user(p);			
				TASK_LEGEND_D->task_finish(who);
				who->set_legend(TASK_48, 5);
				send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,102,"" );
				who->add_cash(500);
				who->add_exp(120);
				who->add_potential(20);
				send_user(who,"%c%s",';',sprintf("Thủ Tục Hợp Tác Kinh nghiệm 120, Tiềm năng 20, Ngân lượng 500, Tân Thủ Y"));
				me->do_welcome(3);
			}
			else
			{
                                	destruct(item); 
                                	send_user( who, "%c%s", '!', "您身上没有空位！");				
			}
		}
		break;
	case 3:
		if (who->get_legend(TASK_48, 5) && !who->get_legend(TASK_48, 6))
		{
			send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf(" %s :\n Muốn hưởng thụ sự kích thích những Kinh nghiệm trải qua đi tìm kho báu, đầu tiên ngươi Tìm Bảo Tàng Đồ, có Tàng Bảo Đồ rồi, mới đi tìm kho báu tiếp được, được rồi, nếu ngươi có thể tìm ra Tàng Bảo Đồ, ngươi quay lại chỗ ta nhé, ta sẽ cho ngươi một manh mối.\n"ESC"Nhận nhiệm vụ\ntalk %x# welcome.4\n"ESC"Rời khỏi",me->get_name(),getoid(me)));
		}
		break;
	case 4:
		if (who->get_legend(TASK_48, 5) && !who->get_legend(TASK_48, 6))
		{	//打开宝箱
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			who->set_legend(TASK_48, 6);
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"Tân Thủ Thôn" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,103,"Kinh Nghiệm Tìm Báu Vật" ); 
			send_user( who, "%c%s", '!', "Nhận nhiệm vụ "HIY"Đi tìm kho báu"NOR"");                       
		}
		break;
	case 5 :
		if ( who->get_legend(TASK_48, 6) && !who->get_legend(TASK_48, 7))
		{
			if( !objectp( item = present("Tàng Bảo Đồ", who, 1, MAX_CARRY) ) || item->is_xunbao() != 1 )
			{
				send_user(who,"%c%s",'!',"你的藏宝图呢?");
				return;	
			}
	//		send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf("%s:\n    拿着你手上的藏宝图一直向南走，到野外最突出那个岛上去找找，就在那个草丛里（88，62），找到那里，你就能挖宝了。这次的奖励可丰厚了，你找到宝物后，去找药店老板，他会给你奖励的。\n"ESC"领取任务\ntalk %x# welcome.7\n"ESC"离开",me->get_name(),getoid(me)));
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_48, 7);
			who->add_exp(180);
			who->add_potential(40);
			who->add_cash(1000);
			send_user(who,"%c%s",';',"Đi tìm kho báu Kinh nghiệm 180, Tiềm năng 40, Ngân lượng 1000");
//			send_user( who, "%c%c%c%w%c", 0x51, 2, 1,TID_NEWBIE_01,"" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,103,"" );
			me->do_welcome(6);
		}
		break;
	case 6:
		if (!who->get_legend(TASK_48, 7) )
			return ;		
		if( !objectp( item = present("Tàng Bảo Đồ", who, 1, MAX_CARRY) ) || item->is_xunbao() != 1 )
		{
			send_user(who,"%c%s",'!',"你的藏宝图呢?");
			return;	
		}
		send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf("%s:\n    拿着你手上的藏宝图一直向南走，到清溪最突出那个岛上好好找找，就在那个草丛里（88，62），找到那里，你就可以挖宝了！当然，这个任务比找到藏宝图的奖励会更多，你是否愿意挑战呢？你找到宝物后，去找药店老板，他会给你想要的东西。\n    做完任务后，用alt+w打开人物属性界面，再使用新手信物就可以快速回到新手村哦！\n"ESC"领取任务\ntalk %x# welcome.7\n"ESC"离开",me->get_name(),getoid(me)));
		break;
	case 7:
		if (!who->get_legend(TASK_48, 7))
			return ;		
		if( !objectp( item = present("Tàng Bảo Đồ", who, 1, MAX_CARRY) ) || item->is_xunbao() != 1 )
		{
			send_user(who,"%c%s",'!',"你的藏宝图呢?");
			return;	
		}
		if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
		who->set_legend(TASK_48, 8);
		send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"Tân Thủ Thôn" );
		send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,104,"Gia Tộc Ngọc Bội" );
		send_user( who, "%c%s", '!', "Nhận nhiệm vụ "HIY"Gia Tộc Ngọc Bội"NOR".");
		break;		
	case 8:
		if ( (who->get_legend(TASK_NEWBIE_01, 7) && !who->get_legend(TASK_NEWBIE_01, 8)))
			send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf("%s:\n    为什么还不去挖宝呢？把挖到的宝物交给药店老板，得拿到多少奖励呀！\n"ESC"离开",me->get_name(),));
		break;
	case 9:
		if (who->get_legend(TASK_48, 6) && !who->get_legend(TASK_48, 7))
		{
			if( !objectp( item = present("Tàng Bảo Đồ", who, 1, MAX_CARRY) ) || item->is_xunbao() != 1 )
			{
				send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf(" %s :\n Ngươi tìm không ra tấm Tàng Bảo Đồ ấy?Có phải Trần Lão Đầu đã lén chôm nó đem giấu? Thế này vậy, ngươi tìm lại lần nữa đi! Nhớ tìm kĩ một tí!\n"ESC"Rời khỏi",me->get_name()));
			}
			else 
				send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf(" %s :\n Nhanh thế đã quay lại ư? Ồ, đúng rồi, tấm Tàng Bảo Đồ trên tay ngươi chính là thứ ngươi đang cần, làm khá lắm.\n"ESC"Hoàn thành nhiệm vụ\ntalk %x# welcome.5\n",me->get_name(),getoid(me)));
		}
		break;
	case 99:
		result = sprintf("%s：\n    不知道去哪里买称心的装备？我告诉你好了。\n"
			"    在新手村和楚国你都能买到通用的装备。新手村都是0级的，而楚国则是贩卖10级的装备。\n"
			"    在"HIR" Triệu Quốc "NOR"可以买到"HIR" 桃花源 "NOR"的装备；\n"
			"    "HIR" Chu Quốc "NOR"有"HIR" Cấm Vệ Quân "NOR"装备的专门店；\n"
			"    "HIR" 蜀山 "NOR"的装备可以在"HIR" Yên Quốc "NOR"购买；\n"
			"    到"HIR" Hàn Quốc "NOR"就可以找到"HIR" 唐门 "NOR"的装备专门店；\n"
			"    在"HIR" Tần Quốc "NOR"能买到"HIR" 昆仑山 "NOR"的装备；\n"
			"    "HIR" 茅山 "NOR"的装备可以到"HIR" Tề Quốc "NOR"寻寻看；\n"
			"    最后"HIR" 云梦泽 "NOR"的装备你只要到"HIR" Ngụy Quốc "NOR"便可以找到了。"
			"\n", me->get_name() );
		send_user( who, "%c%c%w%s", ':', 3, me->get_char_picid(), result );
		break;		
	}
}	               
