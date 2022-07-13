
#include <ansi.h>
#include <equip.h>
#include <task.h>
#include <npc.h>
#include <time.h>


//
void SAVE_BINARY() { }

void do_gift(object me, object who, string arg)
{
	int type = to_int(arg);
	string result, *name,ben4,ben5;
	int iTime, day, p, level, i, size,ben,ben1,ben2,ben3;
	mixed *mxTime;
	object item;
	level = me->get_level();
	if (me->get_save_2("cantuong.status")>=2)
	{
		result = sprintf("%s:\n Ngươi đã làm xong nhiệm vụ này rồi, không thể nhận tiếp.\n", who->get_name());
		result += ESC"Rời khỏi";
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
		return;
	}
	if (me->get_save_2("cantuong.status")==1 &&
		me->get_save_2("cantuong.count")>=10000 &&
		me->get_save_2("cantuong.hv")>=1 &&
		me->get_save_2("cantuong.agbd")>=1 &&
		me->get_save_2("cantuong.uvdtq")>=1 &&
		me->get_save_2("cantuong.ktl")>=1)
	{
		if( USER_INVENTORY_D->get_free_count(me) < 1 )
		{
			send_user(me,"%c%c%w%s",':',3,9959, "Can Tương: \nHành trang của ngươi không đủ 1 ô trống, thu xếp lại hành trang rồi đến gặp ta ! \n"ESC"Xác nhận");
				return;
		}
	if ( me->get_save("nhannvctben")==1 ) ben4="/item/test2/thanbinhpho/1100";
	else if ( me->get_save("nhannvctben")==2 ) ben4="/item/test2/thanbinhpho/2100";
	else if ( me->get_save("nhannvctben")==3 ) ben4="/item/test2/thanbinhpho/3100";
	else if ( me->get_save("nhannvctben")==4 ) ben4="/item/test2/thanbinhpho/4100";
	else if ( me->get_save("nhannvctben")==5 ) ben4="/item/test2/thanbinhpho/5100";
	else if ( me->get_save("nhannvctben")==6 ) ben4="/item/test2/thanbinhpho/6100";
		item=new(ben4);
		p = item->move2(me,-1);
		item->add_to_user(p);
		me->set_save_2("cantuong.status", 2);
		me->delete_save_2("cantuong.count");
		me->delete_save_2("cantuong.hv");
		me->delete_save_2("cantuong.agbd");
		me->delete_save_2("cantuong.uvdtq");
		me->delete_save_2("cantuong.ktl");
	//	me->add_save("cantuongtbp",1);
		send_user( me, "%c%c%c%w%w%s", 0x51, 1, 2, TID_CANTUONG, 1, "" );
		send_user( me, "%c%c%c%w%s", 0x51, 1, 1, TID_CANTUONG, "" );
		result = sprintf("%s:\n Ngươi đã hoàn thành nhiệm vụ tìm kiếm Thần Binh Phổ, ngươi đạt được %s. Bây giờ ngươi hãy thu thập đủ nguyên liệu còn lại và đến gặp ta để nâng cấp Tuyệt thế thần binh !\n", who->get_name(), item->get_name());
		result += ESC"Xác nhận\nCLOSE\n";
		result += ESC"Rời khỏi";
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
		send_user(me,"%c%s",';',sprintf("Bạn nhận được phần thưởng nhiệm vụ "HIY"%s"NOR " !",item->get_name()));
		me->delete_save("nhannvctben");
		return;
	}
	if (level<100)
	{
		result = sprintf("%s:\n Cấp bậc chưa đạt 100, không thể nhận nhiệm vụ.\n", who->get_name());
		result += ESC"Rời khỏi";
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
		return;
	}		
	if (me->get_save_2("cantuong.status")==1)
	{
		result = sprintf("%s:\n Ngươi đã nhận nhiệm vụ rồi, hãy cố gắng hoàn thành !\n", who->get_name());
		result += ESC"Rời khỏi";
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
		return;
	}		
	switch(type)
	{
	case 100:
		result = sprintf("%s:\n Ngươi muốn nhận nhiệm vụ tìm kiếm loại Thần Binh Phổ nào ? Xin hãy lựa chọn !\n", who->get_name());
		result += sprintf(ESC"Tìm kiếm Thần Binh Phổ - Trụ Thiên Quyền Thủ\ntalk %x# nhannv.501\n", getoid(who));
		result += sprintf(ESC"Tìm kiếm Thần Binh Phổ - Đoạt Mệnh Ma Khí\ntalk %x# nhannv.502\n", getoid(who));
		result += sprintf(ESC"Tìm kiếm Thần Binh Phổ - Càn Khôn Vân Đao\ntalk %x# nhannv.503\n", getoid(who));
		result += sprintf(ESC"Tìm kiếm Thần Binh Phổ - Huyết Lệ\ntalk %x# nhannv.504\n", getoid(who));
		result += sprintf(ESC"Tìm kiếm Thần Binh Phổ - Phá Thiên Thương\ntalk %x# nhannv.505\n", getoid(who));
		result += sprintf(ESC"Tìm kiếm Thần Binh Phổ - Hoả Thiên Côn\ntalk %x# nhannv.506\n", getoid(who));
		result += ESC"Huỷ bỏ\n";
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
		break;
	case 501:	
	case 502:	
	case 503:	
	case 504:	
	case 505:	
	case 506:
		if ( type==501 ) { ben3=1; ben5="Thần Binh Phổ - Trụ Thiên Quyền Thủ"; }
		else if ( type==502 ) { ben3=2; ben5="Thần Binh Phổ - Đoạt Mệnh Ma Khí"; }
		else if ( type==503 ) { ben3=3; ben5="Thần Binh Phổ - Càn Khôn Vân Đao"; }
		else if ( type==504 ) { ben3=4; ben5="Thần Binh Phổ - Huyết Lệ"; }
		else if ( type==505 ) { ben3=5; ben5="Thần Binh Phổ - Phá Thiên Thương"; }
		else if ( type==506 ) { ben3=6; ben5="Thần Binh Phổ - Hoả Thiên Côn"; }
		me->set_save("nhannvctben",ben3);
		result = sprintf("%s:\n Để sở hữu Tuyệt thế thần binh không những phải cơ trí, mà còn phải uy dũng hơn người. Ngươi hãy đi tiêu diệt Hổ Vương, Âm Gian Bạn Đồ, Khuyển Thái Lan, Uy Võ Đại Tướng Quân và 10000 quái vật rồi đến gặp ta !.\n", who->get_name());
		result += sprintf(ESC"Nhận nhiệm vụ Tìm kiếm %s\ntalk %x# nhannv.1001\n", ben5, getoid(who));
		result += ESC"Cự tuyệt\n";
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
		break;
	case 1001:	
		if ( me->get_save("nhannvctben") < 1 )
		{
		send_user(me,"%c%c%w%s",':',3,9959, "Can Tương: \nNgươi chưa lựa chọn loại Thần Binh Phổ, không thể nhận nhiệm vụ ! \n"ESC"Xác nhận");
				return;
		}
		ben1 = level-10;
		ben2 = level+10;
		if (ben1>120) ben1 = 120;
		if (ben2>135) ben2 = 135;
		result = sprintf("%s:\n Ngươi đã nhận nhiệm vụ, hãy tiêu diệt 10000 quái vật có đẳng cấp %d~%d đồng thời ngươi cũng phải tiêu diệt Hổ Vương, Âm Gian Bạn Đồ, Khuyển Thái Lan, Uy Võ Đại Tướng Quân.\n", who->get_name(), ben1, ben2);		
		result += ESC"Rời khỏi\n";
		send_user(me, "%c%c%w%s", ':', 3, who->get_char_picid(), result );
		me->delete_save_2("cantuong");
		me->set_save_2("cantuong.status", 1);
		me->set_save_2("cantuong.level", me->get_level());
		me->set_save_2("cantuong.level1", ben1);
		me->set_save_2("cantuong.level2", ben2);
		send_user( me, "%c%c%c%w%s", 0x51, 1, 1, TID_CANTUONG, "Nâng cấp Thần Binh" ); 
		send_user( me, "%c%c%c%w%w%s", 0x51, 1, 2, TID_CANTUONG, 1, "Tìm kiếm Thần Binh Phổ" ); 
		send_user( me, "%c%s", '!', "Bạn nhận nhiệm vụ "HIY"Tìm kiếm Thần Binh Phổ");
		break;	
	}
}

string send_task_intro(object me)
{
	int level, i, size, exp,ben1,ben2;
	string result, *name, result2,ben;
	if (me->get_save_2("cantuong.status")!=1) return "";
	level = me->get_save_2("cantuong.level");
	exp = "/sys/npc/energy"->get_exp_bonus(level);
		ben1 = level-10;
		ben2 = level+10;
		if (ben1>120) ben1 = 120;
		if (ben2>135) ben2 = 135;	
	if ( me->get_save("nhannvctben")==1 ) ben="Thần Binh Phổ - Trụ Thiên Quyền Thủ";
	else if ( me->get_save("nhannvctben")==2 ) ben="Thần Binh Phổ - Đoạt Mệnh Ma Khí";
	else if ( me->get_save("nhannvctben")==3 ) ben="Thần Binh Phổ - Càn Khôn Vân Đao";
	else if ( me->get_save("nhannvctben")==4 ) ben="Thần Binh Phổ - Huyết Lệ";
	else if ( me->get_save("nhannvctben")==5 ) ben="Thần Binh Phổ - Phá Thiên Thương";
	else if ( me->get_save("nhannvctben")==6 ) ben="Thần Binh Phổ - Hoả Thiên Côn";
	result = sprintf(BLK"Mục đích nhiệm vụ:\n"BLK" Tiêu diệt 10000 quái vật có đẳng cấp %d~%d, đồng thời tiêu diệt Hổ Vương, Âm Gian Bạn Đồ, Khuyển Thái Lan, Uy Võ Đại Tướng Quân.\n"HIR " Quái vật"BLK": %d/10000\n"HIR " Hổ Vương"BLK": %d/1\n"HIR " Âm Gian Bạn Đồ"BLK": %d/1\n"HIR " Uy Võ Đại Tướng Quân"BLK": %d/1\n"HIR " Khuyển Thái Lang"BLK": %d/1\n"BLK"Miêu tả nhiệm vụ:\n"BLK" Tiêu diệt 10000 quái vật có đẳng cấp %d~%d tại các khu vực luyện cấp, đồng thời phải tiêu diệt Hổ Vương ( xuất hiện ở Trường Bạch Thiên Trì ), Âm Gian Bạn Đồ ( xuất hiện ở Hầm Vạn Nhân tầng 5 ), Khuyển Thái Lan ( xuất hiện ở Hải Tân 2 ), Uy Võ Đại Tướng Quân ( xuất hiện ở Mục Trường của nước Triệu ). Sau khi tiêu diệt đủ mục tiêu trở về Can Tương để hoàn thành nhiệm vụ.\n"BLK"Phần thưởng: %s.\n",
	  ben1, ben2, me->get_save_2("cantuong.count"),me->get_save_2("cantuong.hv"),me->get_save_2("cantuong.agbd"), 
	  me->get_save_2("cantuong.uvdtq"),me->get_save_2("cantuong.ktl"), ben1, ben2, ben);	                
	return result;	                        
}

void task_giveup(object player )
{
	int time;
	object item;
	send_user( player, "%c%c%c%w%w%s", 0x51, 1, 2, TID_CANTUONG, 1, "" );
	send_user( player, "%c%c%c%w%s", 0x51, 1, 1, TID_CANTUONG, "" );
	player->delete_save_2("cantuong");
	// Can Tương
/*	item = present("Tử Thạch", player, 1, MAX_CARRY*4);
	if (item)
	{
		item->remove_from_user();
	        destruct(item);	
	}	*/       
}