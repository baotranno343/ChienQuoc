/*
Edit by Nguyễn Quang Hiếu
*/
#include <npc.h>
#include <cmd.h>
#include <ansi.h>
#include <equip.h>
#include <time.h>

inherit OFFICER;

// 函数:获取人物造型
void reset();
int get_char_picid() { return 8115; }
int is_seller() { return 6006; }
int is_self_look() { return 1; }
void do_gift(string arg);
void codetanthu();
// 函数:构造处理
void create()
{
	set_name("Thiên Sứ Cứu Độ");
	set_2("talk", (["gift":(
							   : do_gift:),
					  "codetanthu":(
									   : codetanthu:),
	]));

	setup();
}

void do_look(object who)
{
	int id = getoid(this_object());
	send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), sprintf(" %s :\n Ta là sứ giả điểm danh của Chiến Quốc. Ngươi cần gì ở ta ??\n"
																 //
																 ESC "Điểm danh hằng ngày\ntalk %x# gift.56\n"		//
																 ESC "Nhận quà nạp lần đầu\ntalk %x# gift.1\n"		//
																 ESC "Nhận quà đền bù Bảo Trì\ntalk %x# gift.111\n" //
																 ESC "Nhập Code Tân Thủ\ntalk %x# codetanthu\n"

																 // ESC HIY "Đổi trang bị vai vĩnh viễn\ntalk %x# gift.2\n"
																 //
																 // ESC HIG "Tung tích của Huyễn thú\ntalk %x# gift.11\n"
																 ESC "Rời khỏi",
																 get_name(), id, id, id, id, id, id));
}

void do_gift(string arg)
{
	object me = this_object();
	__FILE__->do_gift2(me, arg);
}

void do_gift2(object me, string arg)
{
	int flag, id, i, p, iTime, iDay, iGio, mDay, rate, l, exp, cashkhoa, knbkhoa, n, ngay;
	object who, item, item1;
	string result, *line;
	mixed *mxTime;
	iTime = time();
	mxTime = localtime(iTime);
	mDay = mxTime[TIME_MDAY];
	iDay = mxTime[TIME_YDAY];
	iGio = mxTime[TIME_HOUR];

	who = this_player();
	id = getoid(me);
	flag = to_int(arg);
	who->set_time("talk", 0);
	rate = random(100);
	if (who->get_level() < 10)
	{
		notify("Đẳng cấp của ngươi chưa đạt 10 cấp");
		return;
	}
	switch (flag)
	{
	case 1:
		if (!who->get_save_2("napthe.check"))
		{
			result = me->get_name() + ":\n    Bạn chưa từng nạp thẻ! !\n";
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), result);
			return;
		}
		if (who->get_save_2("napthe.naplandau"))
		{
			result = me->get_name() + ":\n    Bạn đã nhận quà nạp lần đầu rồi !\n";
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), result);
			return;
		}
		if (USER_INVENTORY_D->get_free_count(who) < 2)
		{
			send_user(who, "%c%s", '!', "Hành trang không đủ chỗ.");
			return 0;
		}
		who->set_save_2("napthe.naplandau", 1);
		item = new ("ken/hotrotanthu/naplandau");
		n = item->move2(who, -1);
		item->add_to_user(n);
		item->set_no_give(1);

		result = me->get_name() + ":\n    Bạn nhận quà nạp lần đầu thành công, hãy kiểm tra túi nhé !\n";
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), result);
		return;
		break;
	case 111:

		if (!(line = explode(read_file("quabaotri.txt"), "\n")) || sizeof(line) < 2)
		{
			result = me->get_name() + ":\n    Không tìm thấy dữ liệu đền bù !\n";
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), result);
			return;
		}

		if (sscanf(line[1], "%d:%d:%d", ngay, cashkhoa, knbkhoa) != 3)
		{
			result = me->get_name() + ":\n    Hôm nay không có quà đền bù !\n";
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), result);
			return;
		}
		if (ngay == 0)
		{
			result = me->get_name() + ":\n    Không có quà đền bù!\n";
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), result);
			return;
		}
		if (who->get_save("denbu.day") == ngay)
		{
			result = me->get_name() + ":\n    Bạn đã nhận quà đền bù hôm nay !\n";
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), result);
			return;
		}
		if (mDay != ngay)
		{
			result = me->get_name() + sprintf(":\n    Quà đền bù được phát vào ngày %d!\n", ngay);
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), result);
			return;
		}
		who->add_knbkhoa(knbkhoa);
		who->add_cashkhoa(cashkhoa);
		who->set_save("denbu.day", ngay);
		result = me->get_name() + sprintf(":\n    Bạn nhận quà đền bù thành công nhân được %d Ngân Bảo Khóa %d Ngân Lượng Khóa, hãy kiểm tra túi nhé !\n", knbkhoa, cashkhoa);
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), result);
		return;
		break;
	// case 2:
	// 	send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), sprintf(" %s :\n 30 phần điểm danh mới có thể đổi được 1 trang bị vai vĩnh viễn nha !!\n" ESC HIY "Tiến hành đổi vật phẩm\ntalk %x# gift.5\n" ESC "Rời khỏi", get_name(), id, id, id, id, id, id, id, id, id));
	// 	break;
	// case 3:
	// 	break;
	// case 5:
	// 	send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), sprintf(" %s :\n Hãy chọn trang bị vai mà bạn muốn !!\n" ESC HIY "Vương Giả Phi Phong\ntalk %x# gift.35\n" ESC HIY "Xí Nhiệt Phi Phong\ntalk %x# gift.36\n" ESC HIY "Thánh Linh Chi Dực Vàng Nhạt\ntalk %x# gift.37\n" ESC HIY "Thánh Linh Chi Dực Trắng Thuần\ntalk %x# gift.38\n" ESC "Rời khỏi", get_name(), id, id, id, id, id, id, id, id, id, id));
	// 	break;

	// case 11:
	// 	send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), sprintf(" %s :\n Huyễn thú là linh vật trong trời đất từ thời xa xưa. Chúng tuy nhỏ bé nhưng sức mạnh thì quả thật khôn lường, nếu ngươi đem đến cho ta đủ đá Thiên Hỏa, ta có thể cho ngươi sở hữu 1 con Huyễn thú cho riêng mình !!\n" ESC "Huyễn thú Hỏa Sư\ntalk %x# gift.600\n" ESC "Huyễn thú Hắc Hỏa Sư\ntalk %x# gift.610\n" ESC "Rời khỏi", get_name(), id, id));
	// 	break;

	// case 35:
	// 	if (TASK_LEGEND_D->check_task_item_amount(who, "Huy Chương Điểm Danh") < 30)
	// 	{
	// 		write_user(who, ECHO "Ngươi không có đủ 30 Huy Chương Điểm Danh !");
	// 		return;
	// 	}
	// 	if (USER_INVENTORY_D->get_free_count(who) < 1)
	// 	{
	// 		notify("Hành trang không đủ 1 chỗ trống");
	// 		return;
	// 	}
	// 	TASK_LEGEND_D->check_task_item1(who, "Huy Chương Điểm Danh", 30);
	// 	item1 = new ("/item/ppvacanh/vgpp");
	// 	l = item1->move2(who, -1);
	// 	item1->add_to_user(l);
	// 	USER_D->user_channel(sprintf(HIY "Chúc mừng bằng hữu " HIR " %s " HIY " đổi quà điểm danh và nhận được trang bị " HIC " %s " HIY ".", who->get_name(), item1->get_name()));
	// 	break;
	// case 36:
	// 	if (TASK_LEGEND_D->check_task_item_amount(who, "Huy Chương Điểm Danh") < 30)
	// 	{
	// 		write_user(who, ECHO "Ngươi không có đủ 30 Huy Chương Điểm Danh !");
	// 		return;
	// 	}
	// 	if (USER_INVENTORY_D->get_free_count(who) < 1)
	// 	{
	// 		notify("Hành trang không đủ 1 chỗ trống");
	// 		return;
	// 	}
	// 	TASK_LEGEND_D->check_task_item1(who, "Huy Chương Điểm Danh", 30);
	// 	item1 = new ("/item/ppvacanh/xnpp");
	// 	l = item1->move2(who, -1);
	// 	item1->add_to_user(l);
	// 	USER_D->user_channel(sprintf(HIY "Chúc mừng bằng hữu " HIR " %s " HIY " đổi quà điểm danh và nhận được trang bị " HIC " %s " HIY ".", who->get_name(), item1->get_name()));
	// 	break;
	// case 37:
	// 	if (TASK_LEGEND_D->check_task_item_amount(who, "Huy Chương Điểm Danh") < 30)
	// 	{
	// 		write_user(who, ECHO "Ngươi không có đủ 30 Huy Chương Điểm Danh !");
	// 		return;
	// 	}
	// 	if (USER_INVENTORY_D->get_free_count(who) < 1)
	// 	{
	// 		notify("Hành trang không đủ 1 chỗ trống");
	// 		return;
	// 	}
	// 	TASK_LEGEND_D->check_task_item1(who, "Huy Chương Điểm Danh", 30);
	// 	item1 = new ("/item/ppvacanh/canhnam");
	// 	l = item1->move2(who, -1);
	// 	item1->add_to_user(l);
	// 	USER_D->user_channel(sprintf(HIY "Chúc mừng bằng hữu " HIR " %s " HIY " đổi quà điểm danh và nhận được trang bị " HIC " %s " HIY ".", who->get_name(), item1->get_name()));
	// 	break;
	// case 38:
	// 	if (TASK_LEGEND_D->check_task_item_amount(who, "Huy Chương Điểm Danh") < 30)
	// 	{
	// 		write_user(who, ECHO "Ngươi không có đủ 30 Huy Chương Điểm Danh !");
	// 		return;
	// 	}
	// 	if (USER_INVENTORY_D->get_free_count(who) < 1)
	// 	{
	// 		notify("Hành trang không đủ 1 chỗ trống");
	// 		return;
	// 	}
	// 	TASK_LEGEND_D->check_task_item1(who, "Huy Chương Điểm Danh", 30);
	// 	item1 = new ("/item/ppvacanh/canhnu");
	// 	l = item1->move2(who, -1);
	// 	item1->add_to_user(l);
	// 	USER_D->user_channel(sprintf(HIY "Chúc mừng bằng hữu " HIR " %s " HIY " đổi quà điểm danh và nhận được trang bị " HIC " %s " HIY ".", who->get_name(), item1->get_name()));
	// 	break;
	case 56:
		if (who->get_save("diemdanh.day") == iDay)
		{
			result = me->get_name() + ":\n    Hôm nay đã nhận rồi, ngày mai hãy đến !\n";
			send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), result);
			return;
		}
		if (USER_INVENTORY_D->get_free_count(who) < 1)
		{
			notify("Hành trang không đủ 1 chỗ trống");
			return;
		}

		who->set_save("diemdanh.day", iDay);
		// item = new ("/item/04/0438");
		// i = item->move2(who, -1);
		// item->add_to_user(i);
		exp = 5000 + USER_EXP_D->get_level_exp(who->get_reincarnation(), who->get_level()) / 10;
		cashkhoa = 10000;
		//	knbkhoa = (10 + random(40));
		//	who->add_knbkhoa(knbkhoa);
		who->add_cashkhoa(cashkhoa);
		who->add_exp(exp);
		send_user(who, "%c%s", ':', me->get_name() + sprintf(":\nĐiểm danh thành công. Bạn nhận được, %d kinh nghiệm và %d Ngân Lượng Khóa\n" ESC "Rời khỏi.", exp, cashkhoa));
		break;

	// case 600:
	// 	send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), sprintf(" %s :\n Hỏa sư là Huyễn thú phụ trợ thiên về phòng thủ đề kháng, để có thể sở hữu thì ta cần 299 viên đá Thiên Hỏa. Ngươi có thật sự muốn nhận nuôi loại Huyễn thú này không ?\n" ESC "Đồng ý\ntalk %x# gift.60\n" ESC "Rời khỏi", get_name(), id));
	// 	break;
	// case 610:
	// 	send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), sprintf(" %s :\n Hắc hỏa sư là Huyễn thú phụ trợ thiên về tấn công sát thương, để có thể sở hữu thì ta cần 299 viên đá Thiên Hỏa. Ngươi có thật sự muốn nhận nuôi loại Huyễn thú này không ?\n" ESC "Đồng ý\ntalk %x# gift.61\n" ESC "Rời khỏi", get_name(), id));
	// 	break;
	// case 60:

	// 	if (TASK_LEGEND_D->check_task_item_amount(who, "Thiên Hỏa Thạch Bàn Đơn") < 299)
	// 	{
	// 		notify("Ngươi không có 299 Thiên Hỏa Thạch Bàn Đơn");
	// 		return;
	// 	}
	// 	if (USER_INVENTORY_D->get_free_count(who) < 1)
	// 	{
	// 		notify("Hành trang không đủ 1 chỗ trống");
	// 		return;
	// 	}
	// 	TASK_LEGEND_D->check_task_item1(who, "Thiên Hỏa Thạch Bàn Đơn", 299);
	// 	item = new ("/item/huyenthu/hoasu");
	// 	i = item->move2(who, -1);
	// 	item->add_to_user(i);
	// 	USER_D->user_channel(sprintf("Bằng hữu %s vừa truy lùng và tìm ra tung tích của %s", who->get_name(), item->get_name()));
	// 	send_user(who, "%c%s", ';', "Bạn nhận được " HIR + item->get_name());
	// 	break;
	// case 61:

	// 	if (TASK_LEGEND_D->check_task_item_amount(who, "Thiên Hỏa Thạch Bàn Đơn") < 299)
	// 	{
	// 		notify("Ngươi không có 299 Thiên Hỏa Thạch Bàn Đơn");
	// 		return;
	// 	}
	// 	if (USER_INVENTORY_D->get_free_count(who) < 1)
	// 	{
	// 		notify("Hành trang không đủ 1 chỗ trống");
	// 		return;
	// 	}
	// 	TASK_LEGEND_D->check_task_item1(who, "Thiên Hỏa Thạch Bàn Đơn", 299);
	// 	item = new ("/item/huyenthu/hachoasu");
	// 	i = item->move2(who, -1);
	// 	item->add_to_user(i);
	// 	USER_D->user_channel(sprintf("Bằng hữu %s vừa truy lùng và tìm ra tung tích của %s", who->get_name(), item->get_name()));
	// 	send_user(who, "%c%s", ';', "Bạn nhận được " HIR + item->get_name());
	// 	break;
	default:
		break;
	}
	return;
}
void codetanthu()
{
	object me = this_object();
	object who = this_player();
	string *line;
	int i;
	send_user(who, "%c%c%d%s", '?', 16, 15, "Xin nhập mã Code Tân Thủ    (Tối đa 15 ký tự):\n" ESC "codetanthu + %s\n");
	return;
}