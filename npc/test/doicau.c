/*
Edit by Nguyễn Quang Hiếu
*/
#include <npc.h>
#include <ansi.h>
#include <equip.h>
#include <time.h>
#include <effect.h>
#include <skill.h>

inherit OFFICER;

// 函数:获取人物造型
void reset();
int is_seller() { return 6006; }
int is_self_look() { return 1; }
int get_char_picid() { return 6009; }
void do_gift(string arg);

// 函数:构造处理
void create()
{
	set_name("Tiên Cô Thiên Sứ");
	set_real_name(HIR "Tiểu Long Nữ");

	set_2("talk", (["gift":(
							   : do_gift:),
	]));

	setup();
}

void do_look(object who)
{
	int id = getoid(this_object());
	send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), sprintf(" %s :\n Nếu Ngươi có Hoa Cầu, Lam Cầu, Hồng Cầu, Hắc Cầu có thể đem đến giao cho ta để đổi lấy phần thưởng \nỞ chỗ ta cũng có thể Đổi phần thưởng sau khi Nạp Thẻ !!!\nNgươi muốn đổi thưởng không?????? \n" ESC HIC "Ta muốn đổi phần thưởng....\ntalk %x# gift.2\n" ESC HIC "Ta muốn Nhận thưởng Nạp thẻ....\ntalk %x# gift.3\n" ESC HIG "Ta muốn đổi Cờ Tướng lấy phần thưởng....\ntalk %x# gift.40\n" ESC HIY "Ta muốn đổi Ác Quỷ(vương) lấy phần thưởng....\nlist10 %x#\n" ESC "Rời khỏi", get_name(), id, id, id, id, id, id, id, id));
}

void do_gift(string arg)
{
	object me = this_object();
	__FILE__->do_gift2(me, arg);
}

void do_gift2(object me, string arg)
{
	int flag, id, i, p, iTime, iDay, iGio, rate, l, tien, item1, gioitinh;
	object who, item, item2, item3;
	string *nTmp, cFile, cTmp, cFinal, result;
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
	gioitinh = who->get_gender() == 1 ? 10 : 11;
	switch (flag)
	{
	case 1:
		break;
	case 2:
		send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), sprintf(" %s :\n Ngươi muốn dùng loại Cầu nào để đổi thưởng ?? Nếu có 4 Loại thì càng tốt !!! \n" ESC HIY "[Dùng Hắc Cầu đổi thưởng]\ntalk %x# gift.28\n" ESC HIY "[Dùng Lam Cầu đổi thưởng]\ntalk %x# gift.29\n" ESC HIY "[Dùng Hồng Cầu đổi thưởng]\ntalk %x# gift.30\n" ESC HIY "[Dùng Hoa Cầu đổi thưởng]\ntalk %x# gift.31\n" ESC HIY "[Dùng Hắc + Lam + Hồng + Hoa Cầu đổi thưởng]\ntalk %x# gift.32\n" ESC "Rời khỏi", get_name(), id, id, id, id, id, id, id, id, id));
		break;
	case 3:
		send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), sprintf(" %s :\n Ngươi đã từng Nạp Thẻ ????\nSố điểm tích luỹ Nạp Thẻ của ngươi là " HIB "%d" NOR " . \nNgươi muốn đổi thưởng không ???? \n" ESC HIY "[Nhận Đá Tương Uyên] - 1 điểm\ntalk %x# gift.33\n" ESC HIY "[Nhận 10 Đá Tương Uyên] - 6 điểm\ntalk %x# gift.34\n" ESC HIY "[Nhận Đá Càn Khôn] - 1 điểm\ntalk %x# gift.35\n" ESC HIY "[Nhận 10 Đá Càn Khôn] - 6 điểm\ntalk %x# gift.36\n" ESC HIY "[Nhận Sơ Cấp Đoạn Thạch] - 1 điểm\ntalk %x# gift.37\n" ESC HIY "[Nhận Trung Cấp Đoạn Thạch] - 2 điểm\ntalk %x# gift.38\n" ESC HIY "[Nhận Cao Cấp Đoạn Thạch] - 4 điểm\ntalk %x# gift.39\n" ESC HIG "[HOT] [Thẻ VIP] - 1 điểm\ntalk %x# gift.50\n" ESC "Rời khỏi", get_name(), who->get_save("diemnapknb"), id, id, id, id, id, id, id, id, id));
		break;
	case 28:
		if (TASK_LEGEND_D->check_task_item_amount(who, "Hắc Cầu") < 1)
		{
			notify("Ngươi không có Hắc Cầu");
			return;
		}
		if (USER_INVENTORY_D->get_free_count(who) < 1)
		{
			notify("Hành trang không đủ 1 chỗ trống");
			return;
		}
		TASK_LEGEND_D->check_task_item1(who, "Hắc Cầu", 1);
		if (rate < 20)
		{
			item = new ("/item/test2/TuiQuaVoSong");
			if (!item)
				return 0;
		}
		else if (rate < 45)
		{
			item = new ("/item/test2/TuiThuCuoi");
			if (!item)
				return 0;
		}
		else if (rate < 60)
		{
			item1 = 10;
		}
		else if (rate < 90)
		{
			tien = 20000;
		}
		else
		{
			tien = 10000;
		}
		if (tien)
		{
			who->add_cash(tien);
			send_user(who, "%c%s", '!', sprintf("Bạn nhận được %d ngân lượng", tien));
			//USER_D->user_channel(sprintf(HIG"Bằng hữu "HIY "%s" HIG" vừa đổi Hắc Cầu nhận được:"HIY"%d "HIG "Ngân lượng .", who->get_name(),tien ));
		}
		else if (item)
		{
			l = item->move2(who, -1);
			item->add_to_user(l);
			send_user(who, "%c%s", '!', "Bạn nhận được " HIY + item->get_name());
			//USER_D->user_channel(sprintf(HIG"Bằng hữu "HIY "%s" HIG" vừa đổi Hắc Cầu nhận được: " HIY"%s " HIG " .", who->get_name(),item->get_name() ));
		}
		else if (item1)
		{
			"sys/sys/test_db"->add_yuanbao(who, item1);
			send_user(who, "%c%s", '!', sprintf("Bạn nhận được %d Kim Nguyên Bảo", item1 / 10));
			//USER_D->user_channel(sprintf(HIG"Bằng hữu "HIY "%s" HIG" vừa đổi Hắc Cầu nhận được:"HIY"%d "HIG "Kim Nguyên Bảo .", who->get_name(),item1/10 ));
		}
		return 0;
		break;
	case 29:
		if (TASK_LEGEND_D->check_task_item_amount(who, "Lam Cầu") < 1)
		{
			notify("Ngươi không có Lam Cầu");
			return;
		}
		if (USER_INVENTORY_D->get_free_count(who) < 1)
		{
			notify("Hành trang không đủ 1 chỗ trống");
			return;
		}
		TASK_LEGEND_D->check_task_item1(who, "Lam Cầu", 1);
		if (rate < 20)
		{
			item = new ("/item/test2/TuiQuaVoSong");
			//	item->set_amount(2);
			if (!item)
				return 0;
		}
		else if (rate < 45)
		{
			item = new ("/item/test2/TuiThuCuoi");
			if (!item)
				return 0;
		}
		else if (rate < 60)
		{
			item1 = 15;
		}
		else if (rate < 90)
		{
			tien = 40000;
		}
		else
		{
			tien = 20000;
		}
		if (tien)
		{
			who->add_cash(tien);
			send_user(who, "%c%s", '!', sprintf("Bạn nhận được %d ngân lượng", tien));
			//USER_D->user_channel(sprintf(HIG"Bằng hữu "HIY "%s" HIG" vừa đổi Lam Cầu nhận được:"HIY"%d "HIG "Ngân lượng .", who->get_name(),tien ));
		}
		else if (item)
		{
			l = item->move2(who, -1);
			item->add_to_user(l);
			send_user(who, "%c%s", '!', "Bạn nhận được " HIY + item->get_name());
			//USER_D->user_channel(sprintf(HIG"Bằng hữu "HIY "%s" HIG" vừa đổi Lam Cầu nhận được: " HIY"%s " HIG " .", who->get_name(),item->get_name() ));
		}
		else if (item1)
		{
			"sys/sys/test_db"->add_yuanbao(who, item1);
			send_user(who, "%c%s", '!', sprintf("Bạn nhận được %d Kim Nguyên Bảo", item1 / 10));
			//USER_D->user_channel(sprintf(HIG"Bằng hữu "HIY "%s" HIG" vừa đổi Lam Cầu nhận được:"HIY"%d "HIG "Kim Nguyên Bảo .", who->get_name(),item1/10 ));
		}
		return 0;
		break;
	case 30:
		if (TASK_LEGEND_D->check_task_item_amount(who, "Hồng Cầu") < 1)
		{
			notify("Ngươi không có Hồng Cầu");
			return;
		}
		if (USER_INVENTORY_D->get_free_count(who) < 1)
		{
			notify("Hành trang không đủ 1 chỗ trống");
			return;
		}
		TASK_LEGEND_D->check_task_item1(who, "Hồng Cầu", 1);
		if (rate < 15)
		{
			item = new ("/item/test2/TuiQuaVoSong");
			//	item->set_amount(2);
			if (!item)
				return 0;
		}
		else if (rate < 35)
		{
			item = new ("/item/test2/TuiThuCuoi");
			item->set_amount(2);
			if (!item)
				return 0;
		}
		else if (rate < 45)
		{
			item1 = 20;
		}
		else if (rate < 66)
		{
			item = new ("/item/08/0016");
			item->set_amount(3);
			if (!item)
				return 0;
		}
		else if (rate < 75)
		{
			item = new ("/item/08/0017");
			item->set_amount(3);
			if (!item)
				return 0;
		}
		else if (rate < 90)
		{
			tien = 60000;
		}
		else
		{
			tien = 30000;
		}
		if (tien)
		{
			who->add_cash(tien);
			send_user(who, "%c%s", '!', sprintf("Bạn nhận được %d ngân lượng", tien));
			//USER_D->user_channel(sprintf(HIG"Bằng hữu "HIY "%s" HIG" vừa đổi Hồng Cầu nhận được:"HIY"%d "HIG "Ngân lượng .", who->get_name(),tien ));
		}
		else if (item)
		{
			l = item->move2(who, -1);
			item->add_to_user(l);
			send_user(who, "%c%s", '!', "Bạn nhận được " HIY + item->get_name());
			//USER_D->user_channel(sprintf(HIG"Bằng hữu "HIY "%s" HIG" vừa đổi Hồng Cầu nhận được: " HIY"%s " HIG " .", who->get_name(),item->get_name() ));
		}
		else if (item1)
		{
			"sys/sys/test_db"->add_yuanbao(who, item1);
			send_user(who, "%c%s", '!', sprintf("Bạn nhận được %d Kim Nguyên Bảo", item1 / 10));
			//USER_D->user_channel(sprintf(HIG"Bằng hữu "HIY "%s" HIG" vừa đổi Hồng Cầu nhận được:"HIY"%d "HIG "Kim Nguyên Bảo .", who->get_name(),item1/10 ));
		}
		return 0;
		break;
	case 31:
		if (TASK_LEGEND_D->check_task_item_amount(who, "Hoa Cầu") < 1)
		{
			notify("Ngươi không có Hoa Cầu");
			return;
		}
		if (USER_INVENTORY_D->get_free_count(who) < 1)
		{
			notify("Hành trang không đủ 1 chỗ trống");
			return;
		}
		TASK_LEGEND_D->check_task_item1(who, "Hoa Cầu", 1);
		if (rate < 15)
		{
			item = new ("/item/test2/TuiQuaVoSong");
			item->set_amount(2);
			if (!item)
				return 0;
		}
		else if (rate < 35)
		{
			item = new ("/item/test2/TuiThuCuoi");
			item->set_amount(3);
			if (!item)
				return 0;
		}
		else if (rate < 45)
		{
			item1 = 30;
		}
		else if (rate < 66)
		{
			item = new ("/item/08/0016");
			item->set_amount(5);
			if (!item)
				return 0;
		}
		else if (rate < 75)
		{
			item = new ("/item/08/0017");
			item->set_amount(5);
			if (!item)
				return 0;
		}
		else if (rate < 83)
		{
			item = new ("/item/test2/tuitukim55");
			if (!item)
				return 0;
		}
		else if (rate < 93)
		{
			tien = 80000;
		}
		else
		{
			tien = 40000;
		}
		if (tien)
		{
			who->add_cash(tien);
			send_user(who, "%c%s", '!', sprintf("Bạn nhận được %d ngân lượng", tien));
			//USER_D->user_channel(sprintf(HIG"Bằng hữu "HIY "%s" HIG" vừa đổi Hoa Cầu nhận được:"HIY"%d "HIG "Ngân lượng .", who->get_name(),tien ));
		}
		else if (item)
		{
			l = item->move2(who, -1);
			item->add_to_user(l);
			send_user(who, "%c%s", '!', "Bạn nhận được " HIY + item->get_name());
			//USER_D->user_channel(sprintf(HIG"Bằng hữu "HIY "%s" HIG" vừa đổi Hoa Cầu nhận được: " HIY"%s " HIG " .", who->get_name(),item->get_name() ));
		}
		else if (item1)
		{
			"sys/sys/test_db"->add_yuanbao(who, item1);
			send_user(who, "%c%s", '!', sprintf("Bạn nhận được %d Kim Nguyên Bảo", item1 / 10));
			//USER_D->user_channel(sprintf(HIG"Bằng hữu "HIY "%s" HIG" vừa đổi Hoa Cầu nhận được:"HIY"%d "HIG "Kim Nguyên Bảo .", who->get_name(),item1/10 ));
		}
		return 0;
		break;
	case 32:
		if (TASK_LEGEND_D->check_task_item_amount(who, "Hắc Cầu") < 1 ||
			TASK_LEGEND_D->check_task_item_amount(who, "Lam Cầu") < 1 ||
			TASK_LEGEND_D->check_task_item_amount(who, "Hồng Cầu") < 1 ||
			TASK_LEGEND_D->check_task_item_amount(who, "Hoa Cầu") < 1)
		{
			notify("Ngươi không đủ 4 loại Cầu");
			return;
		}
		if (USER_INVENTORY_D->get_free_count(who) < 1)
		{
			notify("Hành trang không đủ 1 chỗ trống");
			return;
		}
		TASK_LEGEND_D->check_task_item1(who, "Hắc Cầu", 1);
		TASK_LEGEND_D->check_task_item1(who, "Lam Cầu", 1);
		TASK_LEGEND_D->check_task_item1(who, "Hồng Cầu", 1);
		TASK_LEGEND_D->check_task_item1(who, "Hoa Cầu", 1);
		if (rate < 15)
		{
			item = new ("/item/test2/TuiQuaVoSong");
			item->set_amount(3);
			if (!item)
				return 0;
		}
		else if (rate < 25)
		{
			item = new ("/item/test2/TuiPhapBao");
			if (!item)
				return 0;
		}
		else if (rate < 30)
		{
			item = new ("/item/test2/TuiThuCuoi");
			item->set_amount(5);
			if (!item)
				return 0;
		}
		else if (rate < 35)
		{
			item1 = 50;
		}
		else if (rate < 55)
		{
			item = new ("/item/08/0016");
			item->set_amount(10);
			if (!item)
				return 0;
		}
		else if (rate < 65)
		{
			item = new ("/item/08/0017");
			item->set_amount(10);
			if (!item)
				return 0;
		}
		else if (rate < 75)
		{
			item = new ("/item/test2/tuitukim55");
			if (!item)
				return 0;
		}
		else if (rate < 85)
		{
			item = new ("/item/test2/tuitukim85");
			if (!item)
				return 0;
		}
		else if (rate < 92)
		{
			tien = 140000;
		}
		else
		{
			tien = 70000;
		}
		if (tien)
		{
			who->add_cash(tien);
			send_user(who, "%c%s", '!', sprintf("Bạn nhận được %d ngân lượng", tien));
			//USER_D->user_channel(sprintf(HIG"Bằng hữu "HIY "%s" HIG" vừa đổi 4 loại Cầu nhận được:"HIY"%d "HIG "Ngân lượng .", who->get_name(),tien ));
		}
		else if (item)
		{
			l = item->move2(who, -1);
			item->add_to_user(l);
			send_user(who, "%c%s", '!', "Bạn nhận được " HIY + item->get_name());
			//USER_D->user_channel(sprintf(HIG"Bằng hữu "HIY "%s" HIG" vừa đổi 4 loại Cầu nhận được: " HIY"%s " HIG " .", who->get_name(),item->get_name() ));
		}
		else if (item1)
		{
			"sys/sys/test_db"->add_yuanbao(who, item1);
			send_user(who, "%c%s", '!', sprintf("Bạn nhận được %d Kim Nguyên Bảo", item1 / 10));
			//USER_D->user_channel(sprintf(HIG"Bằng hữu "HIY "%s" HIG" vừa đổi 4 loại Cầu nhận được:"HIY"%d "HIG "Kim Nguyên Bảo .", who->get_name(),item1/10 ));
		}
		return 0;
		break;
	case 33:
		if (who->get_save("diemnapknb") < 1)
		{
			notify("Không đủ 1 điểm Tích Luỹ");
			return;
		}
		if (USER_INVENTORY_D->get_free_count(who) < 1)
		{
			notify("Hành trang không đủ 1 chỗ trống");
			return;
		}
		who->add_save("diemnapknb", -1);
		item = new ("/item/08/0016");
		l = item->move2(who, -1);
		item->add_to_user(l);
		send_user(who, "%c%s", '!', "Bạn nhận được " HIY + item->get_name());
		break;
	case 34:
		if (who->get_save("diemnapknb") < 6)
		{
			notify("Không đủ 6 điểm Tích Luỹ");
			return;
		}
		if (USER_INVENTORY_D->get_free_count(who) < 1)
		{
			notify("Hành trang không đủ 1 chỗ trống");
			return;
		}
		who->add_save("diemnapknb", -6);
		item = new ("/item/08/0016");
		item->set_amount(10);
		l = item->move2(who, -1);
		item->add_to_user(l);
		send_user(who, "%c%s", '!', "Bạn nhận được " HIY + item->get_name());
		break;
	case 35:
		if (who->get_save("diemnapknb") < 1)
		{
			notify("Không đủ 1 điểm Tích Luỹ");
			return;
		}
		if (USER_INVENTORY_D->get_free_count(who) < 1)
		{
			notify("Hành trang không đủ 1 chỗ trống");
			return;
		}
		who->add_save("diemnapknb", -1);
		item = new ("/item/08/0017");
		l = item->move2(who, -1);
		item->add_to_user(l);
		send_user(who, "%c%s", '!', "Bạn nhận được " HIY + item->get_name());
		break;
	case 36:
		if (who->get_save("diemnapknb") < 6)
		{
			notify("Không đủ 6 điểm Tích Luỹ");
			return;
		}
		if (USER_INVENTORY_D->get_free_count(who) < 1)
		{
			notify("Hành trang không đủ 1 chỗ trống");
			return;
		}
		who->add_save("diemnapknb", -6);
		item = new ("/item/08/0017");
		item->set_amount(10);
		l = item->move2(who, -1);
		item->add_to_user(l);
		send_user(who, "%c%s", '!', "Bạn nhận được " HIY + item->get_name());
		break;
	case 37:
		if (who->get_save("diemnapknb") < 1)
		{
			notify("Không đủ 1 điểm Tích Luỹ");
			return;
		}
		if (USER_INVENTORY_D->get_free_count(who) < 1)
		{
			notify("Hành trang không đủ 1 chỗ trống");
			return;
		}
		who->add_save("diemnapknb", -1);
		item = new ("/item/sell/0032");
		l = item->move2(who, -1);
		item->add_to_user(l);
		send_user(who, "%c%s", '!', "Bạn nhận được " HIY + item->get_name());
		break;
	case 38:
		if (who->get_save("diemnapknb") < 2)
		{
			notify("Không đủ 2 điểm Tích Luỹ");
			return;
		}
		if (USER_INVENTORY_D->get_free_count(who) < 1)
		{
			notify("Hành trang không đủ 1 chỗ trống");
			return;
		}
		who->add_save("diemnapknb", -2);
		item = new ("/item/sell/1032");
		l = item->move2(who, -1);
		item->add_to_user(l);
		send_user(who, "%c%s", '!', "Bạn nhận được " HIY + item->get_name());
		break;
	case 39:
		if (who->get_save("diemnapknb") < 4)
		{
			notify("Không đủ 4 điểm Tích Luỹ");
			return;
		}
		if (USER_INVENTORY_D->get_free_count(who) < 1)
		{
			notify("Hành trang không đủ 1 chỗ trống");
			return;
		}
		who->add_save("diemnapknb", -4);
		item = new ("/item/sell/2032");
		l = item->move2(who, -1);
		item->add_to_user(l);
		send_user(who, "%c%s", '!', "Bạn nhận được " HIY + item->get_name());
		break;
	case 40:
		if (TASK_LEGEND_D->check_task_item_amount(who, "Cờ Tướng") < 40)
		{
			notify("Ngươi không có 40 Cờ Tướng");
			return;
		}
		if (USER_INVENTORY_D->get_free_count(who) < 1)
		{
			notify("Hành trang không đủ 1 chỗ trống");
			return;
		}
		TASK_LEGEND_D->check_task_item1(who, "Cờ Tướng", 40);
		if (rate < 10)
		{
			item = new ("/item/sell/1032");
			if (!item)
				return 0;
		}
		else if (rate < 15)
		{
			item = new ("/item/sell/0032");
			if (!item)
				return 0;
		}
		else if (rate < 25)
		{
			item = new ("/item/100/10057");
			if (!item)
				return 0;
		}
		else if (rate < 32)
		{
			item = new ("/item/100/11058");
			if (!item)
				return 0;
		}
		else if (rate < 40)
		{
			item = new (sprintf("/item/100/%d051", gioitinh));
			if (!item)
				return 0;
		}
		else if (rate < 60)
		{
			item = new ("/item/100/11052");
			if (!item)
				return 0;
		}
		else if (rate < 70)
		{
			item = new (sprintf("/item/100/%d053", gioitinh));
			if (!item)
				return 0;
		}
		else if (rate < 80)
		{
			item = new ("/item/100/10054");
			if (!item)
				return 0;
		}
		else
		{
			item = new (sprintf("/item/100/%d055", gioitinh));
			if (!item)
				return 0;
		}
		if (item)
		{
			l = item->move2(who, -1);
			item->add_to_user(l);
			send_user(who, "%c%s", '!', "Bạn nhận được " HIY + item->get_name());
			USER_D->user_channel(sprintf("Bằng hữu " HIG "%s " NOR " vừa đổi Cờ Tướng nhận được: " HIC "%s " HIG " .", who->get_name(), item->get_name()));
		}
		return 0;
		break;
	case 50:
		if (who->get_save("diemnapknb") < 1)
		{
			notify("Không đủ 1 điểm Tích Luỹ");
			return;
		}
		if (TASK_LEGEND_D->check_task_item_amount(who, "Thẻ VIP") >= 1)
		{
			notify("Ngươi đã có Thẻ VIP rồi");
			return;
		}
		if (USER_INVENTORY_D->get_free_count(who) < 1)
		{
			notify("Hành trang không đủ 1 chỗ trống");
			return;
		}
		who->add_save("diemnapknb", -1);
		item = new ("/item/test2/TheVip");
		l = item->move2(who, -1);
		item->add_to_user(l);
		send_user(who, "%c%s", '!', "Bạn nhận được " HIY + item->get_name());
		USER_D->user_channel(sprintf("Bằng hữu " HIG "%s " NOR " vừa thành công đổi được: " HIC "%s " HIG " .", who->get_name(), item->get_name()));
		break;
	}
}
