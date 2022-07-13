#include <npc.h>
#include <cmd.h>
#include <task.h>
#include <ansi.h>
#include <equip.h>
#include <time.h>
#include <effect.h>
#include <skill.h>

inherit OFFICER;

// 函数:获取人物造型
int get_char_picid() { return 9956; }
void do_gift(string arg);

// 函数:构造处理
void create()
{
	set_name("Chiến Quốc Đại Sư");
	set_real_name("Trâu Diễn");
	set_2("talk", (["gift":(
							   : do_gift:),
	]));

	setup();
}

void do_look(object who)
{
	int id = getoid(this_object());
	send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), sprintf(" %s :\n Huyết dục thần binh là vũ khí lợi hại nhất. Dùng khí huyết cộng với nội công thâm sâu mới có thể luyện thành. Người không biết cách sử dụng sẽ bị tâm ma bộc phát, khống chế bản thân. Tà niệm sẽ nổi dậy, rất nguy hiểm...!\n" ESC "Chế tạo Huyết Binh\ntalk %x# gift.10\n" ESC "Hợp thành Tín vật cấp 3\ntalk %x# gift.30\n" ESC "Hợp thành Tín vật cấp 4\ntalk %x# gift.40\n" ESC "Hợp thành Cao Cấp Đoạn Thạch Bị Khắc Dính\ntalk %x# gift.50\n" ESC "Rời khỏi", get_name(), id, id, id, id, id, id, id, id));
}

void do_gift(string arg)
{
	object me = this_object();
	__FILE__->do_gift2(me, arg);
}

void do_gift2(object me, string arg)
{
	int flag, id, i, p, iTime, iDay, iGio, rate, l, tien, ben, tet1 = 0, tet2 = 0, tet3, tet4, bennhat2, bn2;
	object who, item, item1, item2, item3;
	string *nTmp, cFile, cTmp, cFinal, result, bennhat, bn;
	mixed *mxTime;
	iTime = time();
	mxTime = localtime(iTime);
	iDay = mxTime[TIME_YDAY];
	iGio = mxTime[TIME_HOUR];

	who = this_player();
	id = getoid(me);
	flag = to_int(arg);
	who->set_time("talk", 0);
	rate = random(100);
	if (USER_INVENTORY_D->get_free_count(who) < 1)
	{
		notify("Hành trang không đủ 1 chỗ trống");
		return;
	}
	switch (flag)
	{
	case 10:
		send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), sprintf(" %s :\n Muốn chế tạo huyết binh sẽ phải tẩy luyện toàn bộ cấp rèn sao và tinh luyện linh thạch hiện có của trang bị. Ngươi thực sự muốn làm không ?!\n" ESC "Ta hiểu rồi, tiến hành thôi!\ntalk %x# gift.100\n" ESC "Rời khỏi", get_name(), id, id, id));
		break;

	case 100:
		send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), sprintf(" %s :\n Huyết dục thần binh là vũ khí lợi hại nhất. Dùng khí huyết cộng với nội công thâm sâu mới có thể luyện thành. Người không biết cách sử dụng sẽ bị tâm ma bộc phát, khống chế bản thân. Tà niệm sẽ nổi dậy, rất nguy hiểm...!\n" ESC HIG "Diệt Phách Chi Thủ\ntalk %x# gift.101\n" ESC HIG "Bạo Huyết Chi Tiễn\ntalk %x# gift.102\n" ESC HIG "Phá Huyết Cuồng Đao\ntalk %x# gift.103\n" ESC HIG "Phá Pháp Chi Kiếm\ntalk %x# gift.104\n" ESC HIG "Tử Huyết Chi Thương\ntalk %x# gift.105\n" ESC HIG "Bạo Huyết Vũ Côn\ntalk %x# gift.106\n" ESC "Rời khỏi", get_name(), id, id, id, id, id, id, id, id, id, id));
		break;
	case 101:
		if (TASK_LEGEND_D->check_task_item_amount(who, "Mảnh ghép công thức Huyết Binh") < 199 || TASK_LEGEND_D->check_task_item_amount(who, "Ngọc La Quyền Thủ") < 1)
		{
			notify("Ngươi không có 199 Mảnh ghép công thức Huyết Binh Và Ngọc La Quyền Thủ");
			return;
		}
		TASK_LEGEND_D->check_task_item1(who, "Mảnh ghép công thức Huyết Binh", 199);
		TASK_LEGEND_D->check_task_item1(who, "Ngọc La Quyền Thủ", 1);
		item = new ("/item/70/9130");
		i = item->move2(who, -1);
		item->add_to_user(i);
		USER_D->user_channel(sprintf(HIY "Nghe nói bằng hữu " HIR " %s " HIY " đã hợp thành thành công thần binh tuyệt thế " HIC " %s " HIY " Thiên hạ sắp có chuyển biến mới !!", who->get_name(), item->get_name()));
		send_user(who, "%c%s", ';', "Bạn nhận được trang bị " HIR + item->get_name());
		break;
	case 102:
		if (TASK_LEGEND_D->check_task_item_amount(who, "Mảnh ghép công thức Huyết Binh") < 199 || TASK_LEGEND_D->check_task_item_amount(who, "Thần Tiên Hạc Kim") < 1)
		{
			notify("Ngươi không có 199 Mảnh ghép công thức Huyết Binh Và Thần Tiên Hạc Kim");
			return;
		}
		TASK_LEGEND_D->check_task_item1(who, "Mảnh ghép công thức Huyết Binh", 199);
		TASK_LEGEND_D->check_task_item1(who, "Thần Tiên Hạc Kim", 1);
		item = new ("/item/71/9130");
		i = item->move2(who, -1);
		item->add_to_user(i);
		USER_D->user_channel(sprintf(HIY "Nghe nói bằng hữu " HIR " %s " HIY " đã hợp thành thành công thần binh tuyệt thế " HIC " %s " HIY " Thiên hạ sắp có chuyển biến mới !!", who->get_name(), item->get_name()));
		send_user(who, "%c%s", ';', "Bạn nhận được trang bị " HIR + item->get_name());
		break;
	case 103:
		if (TASK_LEGEND_D->check_task_item_amount(who, "Mảnh ghép công thức Huyết Binh") < 199 || TASK_LEGEND_D->check_task_item_amount(who, "Đao Tử Vân") < 1)
		{
			notify("Ngươi không có 199 Mảnh ghép công thức Huyết Binh Và Đao Tử Vân");
			return;
		}
		TASK_LEGEND_D->check_task_item1(who, "Mảnh ghép công thức Huyết Binh", 199);
		TASK_LEGEND_D->check_task_item1(who, "Đao Tử Vân", 1);
		item = new ("/item/72/9130");
		i = item->move2(who, -1);
		item->add_to_user(i);
		USER_D->user_channel(sprintf(HIY "Nghe nói bằng hữu " HIR " %s " HIY " đã hợp thành thành công thần binh tuyệt thế " HIC " %s " HIY " Thiên hạ sắp có chuyển biến mới !!", who->get_name(), item->get_name()));
		send_user(who, "%c%s", ';', "Bạn nhận được trang bị " HIR + item->get_name());
		break;
	case 104:
		if (TASK_LEGEND_D->check_task_item_amount(who, "Mảnh ghép công thức Huyết Binh") < 199 || TASK_LEGEND_D->check_task_item_amount(who, "Lục Tiên Kiếm") < 1)
		{
			notify("Ngươi không có 199 Mảnh ghép công thức Huyết Binh Và Lục Tiên Kiếm");
			return;
		}
		TASK_LEGEND_D->check_task_item1(who, "Mảnh ghép công thức Huyết Binh", 199);
		TASK_LEGEND_D->check_task_item1(who, "Lục Tiên Kiếm", 1);
		item = new ("/item/73/9130");
		i = item->move2(who, -1);
		item->add_to_user(i);
		USER_D->user_channel(sprintf(HIY "Nghe nói bằng hữu " HIR " %s " HIY " đã hợp thành thành công thần binh tuyệt thế " HIC " %s " HIY " Thiên hạ sắp có chuyển biến mới !!", who->get_name(), item->get_name()));
		send_user(who, "%c%s", ';', "Bạn nhận được trang bị " HIR + item->get_name());
		break;
	case 105:
		if (TASK_LEGEND_D->check_task_item_amount(who, "Mảnh ghép công thức Huyết Binh") < 199 || TASK_LEGEND_D->check_task_item_amount(who, "Lục Thần Thương") < 1)
		{
			notify("Ngươi không có 199 Mảnh ghép công thức Huyết Binh Và Lục Thần Thương");
			return;
		}
		TASK_LEGEND_D->check_task_item1(who, "Mảnh ghép công thức Huyết Binh", 199);
		TASK_LEGEND_D->check_task_item1(who, "Lục Thần Thương", 1);
		item = new ("/item/74/9130");
		i = item->move2(who, -1);
		item->add_to_user(i);
		USER_D->user_channel(sprintf(HIY "Nghe nói bằng hữu " HIR " %s " HIY " đã hợp thành thành công thần binh tuyệt thế " HIC " %s " HIY " Thiên hạ sắp có chuyển biến mới !!", who->get_name(), item->get_name()));
		send_user(who, "%c%s", ';', "Bạn nhận được trang bị " HIR + item->get_name());
		break;
	case 106:
		if (TASK_LEGEND_D->check_task_item_amount(who, "Mảnh ghép công thức Huyết Binh") < 199 || TASK_LEGEND_D->check_task_item_amount(who, "Phàn Thiên Côn") < 1)
		{
			notify("Ngươi không có 199 Mảnh ghép công thức Huyết Binh Và Phàn Thiên Côn");
			return;
		}
		TASK_LEGEND_D->check_task_item1(who, "Mảnh ghép công thức Huyết Binh", 199);
		TASK_LEGEND_D->check_task_item1(who, "Phàn Thiên Côn", 1);
		item = new ("/item/75/9130");
		i = item->move2(who, -1);
		item->add_to_user(i);
		USER_D->user_channel(sprintf(HIY "Nghe nói bằng hữu " HIR " %s " HIY " đã hợp thành thành công thần binh tuyệt thế " HIC " %s " HIY " Thiên hạ sắp có chuyển biến mới !!", who->get_name(), item->get_name()));
		send_user(who, "%c%s", ';', "Bạn nhận được trang bị " HIR + item->get_name());
		break;

	case 30:
		send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), sprintf(" %s :\n Hợp thành Phượng hoàng Ngọc bội cần phải có 5 Kỳ lân Ngọc bội. Ngươi đã mang đến đủ chưa ?\n" ESC HIY "Ta có đủ rồi\ntalk %x# gift.32\n" ESC "Rời khỏi", get_name(), id, id, id, id, id, id, id, id, id, id));
		break;
	case 32:
		if (TASK_LEGEND_D->check_task_item_amount(who, "Kỳ Lân Ngọc Bội") < 5)
		{
			write_user(who, ECHO "Ngươi không có đủ 5 Kỳ Lân Ngọc Bội !");
			return;
		}
		if (USER_INVENTORY_D->get_free_count(who) < 1)
		{
			notify("Hành trang không đủ 1 chỗ trống");
			return;
		}
		TASK_LEGEND_D->check_task_item1(who, "Kỳ Lân Ngọc Bội", 5);
		item1 = new ("/item/01/0008");
		l = item1->move2(who, -1);
		item1->add_to_user(l);
		send_user(who, "%c%s", ';', HIY "Chúc mừng bạn hợp thành Phượng Hoàng Ngọc Bội thành công!");
		break;
	case 40:
		send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), sprintf(" %s :\n Hợp thành Phượng Vũ Ngọc bội cần phải có 4 Phượng Hoàng Ngọc bội. Ngươi đã mang đến đủ chưa ?\n" ESC HIY "Ta có đủ rồi\ntalk %x# gift.42\n" ESC "Rời khỏi", get_name(), id, id, id, id, id, id, id, id, id, id));
		break;
	case 42:
		if (TASK_LEGEND_D->check_task_item_amount(who, "Phượng Hoàng Ngọc Bội") < 4)
		{
			write_user(who, ECHO "Ngươi không có đủ 4 Phượng Hoàng Ngọc Bội !");
			return;
		}
		if (USER_INVENTORY_D->get_free_count(who) < 1)
		{
			notify("Hành trang không đủ 1 chỗ trống");
			return;
		}
		TASK_LEGEND_D->check_task_item1(who, "Phượng Hoàng Ngọc Bội", 4);
		item1 = new ("/item/01/0009");
		l = item1->move2(who, -1);
		item1->add_to_user(l);
		send_user(who, "%c%s", ';', HIY "Chúc mừng bạn hợp thành Phượng Hoàng Ngọc Bội thành công!");
		break;
	case 50:
		send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), sprintf(" %s :\n Cao Cấp Đoạn Thạch Khắc Dính nếu ép thất bại sẽ không bị rớt sao, Hợp thành Cao Cấp Đoạn Thạch Khắc Dính cần phải có 5 Cao Cấp Đoạn Thạch Kết Dính. Ngươi đã mang đến đủ chưa ?\n" ESC HIY "Ta có đủ rồi\ntalk %x# gift.52\n" ESC "Rời khỏi", get_name(), id, id, id, id, id, id, id, id, id, id));
		break;
	case 52:
		if (TASK_LEGEND_D->check_task_item_amount(who, "Cao Cấp Đoạn Thạch bị kết dính") < 5)
		{
			write_user(who, ECHO "Ngươi không có đủ 5 Cao Cấp Đoạn Thạch bị kết dính !");
			return;
		}
		if (USER_INVENTORY_D->get_free_count(who) < 1)
		{
			notify("Hành trang không đủ 1 chỗ trống");
			return;
		}
		TASK_LEGEND_D->check_task_item1(who, "Cao Cấp Đoạn Thạch bị kết dính", 5);
		item1 = new ("/item/sell/3032_2");
		l = item1->move2(who, -1);
		item1->add_to_user(l);
		send_user(who, "%c%s", ';', HIY "Chúc mừng bạn hợp thành Cao Cấp Đoạn Thạch bị khắc dính thành công!");
		break;
	}
}
