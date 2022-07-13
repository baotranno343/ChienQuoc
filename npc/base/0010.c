
// 自动生成：/make/npc/make0010

#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>

inherit OFFICER;

void do_goto( string arg );
void do_welcome( string arg );

// 函数：获取人物造型
int get_char_picid() { return 5410; }

// 函数：构造处理
void create()
{
        set_name("Chủ Dịch Trạm");
        set_city_name("Tân Thủ Thôn");

        set_2( "talk", ([
                "goto"    : (: do_goto :),
                "welcome"          : (: do_welcome :),
        ]));
//        set("level", 2);
//        set("legend", ({ 44 }));
//	set("mpLegend",([0:({32*48+12, 32*1+12,}),]));
	set("mpLegend2",([0:({32*48+12,}),]));
        setup();
}

// 函数：对话处理
void do_look( object who )
{
	string tmp;
//	if ( who->get_legend(TASK_NEWBIE_01, 10)&&!who->get_legend(TASK_NEWBIE_01, 11) )
	if ( who->get_legend(TASK_48, 11) && !who->get_legend(TASK_48, 12) )
	{
		tmp = sprintf( " %s :\n "+"/quest/word"->get_normal_word(this_object()) + "\n"+
               		sprintf(ESC  +HIY+ "Hỏi Thăm Tin Tức\ntalk %x# welcome.1\n",getoid(this_object())),get_name()) ;	
	}
//	if ( !who->get_legend(TASK_NEWBIE_01, 12) )
	if ( who->get_legend(TASK_48, 12) && !who->get_legend(TASK_48, 13) )
	{
		if ( !stringp(tmp) )
			tmp = sprintf( " %s :\n "+"/quest/word"->get_normal_word(this_object()) + "\n"+
               			sprintf(ESC  +HIY+ "Phi Cáp Truyền Thư\ntalk %x# welcome.3\n",getoid(this_object())),get_name()) ;	
			
		else
			tmp +=	 sprintf(ESC  +HIY+ "Phi Cáp Truyền Thư\ntalk %x# welcome.3\n",getoid(this_object())) ;	
	}
	if ( stringp(tmp) )
	{
		tmp += ESC"Rời khỏi";
		send_user( who, "%c%s", ':',tmp);
	}	
	else
		"/sys/task/travel"->do_look(this_object(), who);        
}

// 函数：移动处理
void do_goto( string  arg )
{
	"/sys/task/travel"->do_goto(this_object(), this_player(), arg);     
}

void do_welcome( string arg )
{
        object me = this_object();
        __FILE__ ->do_welcome2(me, arg);
}

void do_welcome2( object me, string arg )
{
        int flag,p;
        object who, item;     
        string result;
        who = this_player();
        flag = to_int(arg);
        who->set_time( "talk",  0);
        switch(flag)
        {
	case 1:	
//		if ( !who->get_legend(TASK_NEWBIE_01, 10)||who->get_legend(TASK_NEWBIE_01, 11) )
//			return;
		if ( who->get_legend(TASK_48, 11) && !who->get_legend(TASK_48, 12) )
		send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf(" %s :\n Chủ Tiệm Y Dược này thật tận tâm, giao việc này cho ta, ngươi cứ yên tâm, đợi ta dò la tin tức của hắn, ta sẽ cho người mang tin đến Chủ Tiệm Y Dược, ngươi cứ nhận thù lao của mình trước, mau đi đi!\n"ESC"Hoàn thành nhiệm vụ\ntalk %x# welcome.2\n"ESC"Rời khỏi",me->get_name(),getoid(me)));
			
		break;        	
	case 2:	
//		if ( !who->get_legend(TASK_NEWBIE_01, 10)||who->get_legend(TASK_NEWBIE_01, 11) )
//			return;
//		item = new("/item/91/9110");
//		if ( !item )
//			return ;
//		item->set_amount(10);
//                p =item->move(who, -1);
//                if ( p == 0 )
//                {
//                	destruct(item); 
//                	send_user( who, "%c%s", '!', "您身上没有足够的空位！");
//                	return ;
//                }
//                item->add_to_user(p);

		if ( who->get_legend(TASK_48, 11) && ! who->get_legend(TASK_48, 12))
		{
			TASK_LEGEND_D->task_finish(who);
			who->set_legend(TASK_48, 12);
			who->add_exp(290);
			who->add_potential(20);
			who->add_cash(500);
			send_user(who,"%c%s",';',"Thăm Bệnh Nhân Kinh nghiệm 290, Tiềm năng 20 Ngân lượng 500");
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,105,"" );		
		me->do_welcome(3);
		}
		break;
	case 3:	
//		if ( who->get_legend(TASK_NEWBIE_01, 12)&&who->get_legend(TASK_NEWBIE_01, 13) )
//			return;
//		if ( !who->get_legend(TASK_NEWBIE_01, 12) )
		if ( who->get_legend(TASK_48, 12) && !who->get_legend(TASK_48, 13) )
			send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf(" %s :\n Cuối cùng ngươi cũng đến, ta đã đợi lâu rồi, sáng nay có một bức thư đưa đến, là đơn xuất hàng cho Chủ Tiệm Tạp Hóa, ta thật không tìm được người thay ta mang đi, ngươi xem chỗ ta, bận như là gì, ngươi có muốn giúp ta không?Chủ Tiệm Tạp Hóa ở phía tây bắc ta, ngươi có thể giao bức thư bồ câu này an toàn, hắn có thể sẽ thưởng cho ngươi.\n"ESC"Nhận nhiệm vụ\ntalk %x# welcome.4\n"ESC"Rời khỏi",me->get_name(),getoid(me)));
//		else if ( !who->get_legend(TASK_NEWBIE_01, 13) ) 
//			send_user( who, "%c%c%w%s", ':',3,me->get_char_picid(), sprintf("%s:\n    信送到了吗？是出货单哦，应该比较急的，你可得尽快，耽误了别人发货做生意可就不好了。\n"ESC"离开",me->get_name()));
		break;     
	case 4 :
//		if ( who->get_legend(TASK_NEWBIE_01, 12)&&who->get_legend(TASK_NEWBIE_01, 13) )
//			return;
		if ( who->get_legend(TASK_48, 12) && !who->get_legend(TASK_48, 13) )
		{
			if ( TASK_LEGEND_D->can_task_add(who) != 1 ) return;
			item = new("/item/98/9881");
			if ( !item )
				return ;
	                p =item->move(who, -1);
	                if ( p == 0 )
	                {
	                	destruct(item); 
	                	send_user( who, "%c%s", '!', "您身上没有足够的空位！");
	                	return ;
	                }
	                item->add_to_user(p);
			who->set_legend(TASK_48, 13);	
			send_user( who, "%c%c%c%w%s", 0x51, 2, 1,TID_NEWBIE_01,"Tân Thủ Thôn" );
			send_user( who, "%c%c%c%w%w%s", 0x51, 2, 2,TID_NEWBIE_01,106,"Phi Cáp Truyền Thư" );
			send_user(who,"%c%s",';',"Ngươi cần đến "HIY"Đơn xuất hàng");
			send_user( who, "%c%s", '!', "Nhận nhiệm vụ "HIY"Phi Cáp Truyền Thư"NOR"");
		}
		break;
	}		
}
