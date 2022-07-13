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
int get_char_picid() { return 7301; }
void do_gift(string arg);
// 函数：小贩识别
int is_seller() { return 4; }
// 有自己的do_look函数
int is_self_look() { return 1; }

void create()
{
	set_real_name("Lão Bà Bà");
	set_name("Event 8 tháng 3");
	set_2("good", (["01":"/item/event/83/hoahong",
					  "02":"/item/event/83/hoacuc",
					  "03":"/item/event/83/hoasen",
					  "04":"/item/event/83/hoadao",
					  "05":"/item/event/83/hoahue",
	]));
	set_2("talk", (["gift":(
							   : do_gift:),
	]));

	setup();
}

void do_look(object who)
{
	int id = getoid(this_object());
	object me = this_object();
	string result;
	send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), sprintf(" %s :\n Nào nào các cháu nhỏ, hãy lại shop của lão nương mua Hoa. Ngoài ra ta cũng rất thích những cậu bé hiếu thảo, nào nào, các bạn nhỏ muốn gì? \n" ESC "Shop Hoa\nlist %x#\n" ESC "Đổi điểm Hiếu Thảo\ntalk %x# gift.1\n" ESC "Rời khỏi", get_name(), id, id, id, id, id));
}

void do_gift(string arg)
{
	object me = this_object();
	__FILE__->do_gift2(me, arg);
}

void do_gift2(object me, string arg)
{
	int flag, id, i, p, iTime, iDay, iGio, rate, l, tien, ben, tet1 = 0, tet2 = 0, tet3, tet4, diemhtcanco, tile;
	object who, item, item1, item2, item3;
	string *nTmp, cFile, cTmp, cFinal, result, vatpham, bn;
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
	switch (flag)
	{
	case 1:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf("%s: \nĐiểm Hiếu Thảo hiện tại của cưng là %d điểm. \nCưng muốn nhận phần thưởng nào? Xin hãy lựa chọn (Có tỉ lệ thất bại đó nha): \n" ESC "5 điểm tích lấy Tử Sâm Đơn ( tỷ lệ đổi thành công là 100%% )\ntalk %x# gift.11\n" ESC "15 điểm tích lấy Ngân Lượng Ngẫu Nhiên ( tỷ lệ đổi thành công là 80%% )\ntalk %x# gift.12\n" ESC "20 điểm tích lấy Kim Bảo Ngẫu Nhiên ( tỷ lệ đổi thành công là 70%% )\ntalk %x# gift.13\n"
																		 // ESC "50 điểm tích lấy Siêu Cấp Đoạn Thạch ( tỷ lệ đổi thành công là 35%% )\ntalk %x# gift.14\n"
																		 ESC "Rời khỏi",
																		 me->get_name(), who->get_save("diemhieuthao"), id, id, id, id, id, id, id, id));
		break;
	case 11:
	case 12:
	case 13:
	case 14:
		if (flag == 11)
		{
			vatpham = "item/91/9167";
			diemhtcanco = 5;
			tile = 100;
		}

		else if (flag == 12)
		{
			vatpham = "item/event/83/tuinganluong";
			diemhtcanco = 15;
			tile = 80;
		}
		else if (flag == 13)
		{
			vatpham = "item/event/83/tuikimbao";
			diemhtcanco = 20;
			tile = 70;
		}
		else if (flag == 14)
		{
			return;
		}
		// else if (flag == 14)
		// {
		// 	vatpham = "item/sell/5032";
		// 	diemhtcanco = 50;
		// 	tile = 35;
		// }
		if (who->get_save("diemhieuthao") < diemhtcanco)
		{
			send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), "Lão Bà Bà :\nCưng không có đủ " + diemhtcanco + " lòng Hiếu Thảo rồi !\n" ESC "Xác nhận \nCLOSE\n" ESC "Rời khỏi");
			return;
		}
		if (USER_INVENTORY_D->get_free_count(who) < 1)
		{
			send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), "Lão Bà Bà :\nHành trang của cưng không đủ !\n" ESC "Xác nhận \nCLOSE\n" ESC "Rời khỏi");
			return;
		}
		who->add_save("diemhieuthao", -diemhtcanco);
		if (random100() < tile)
			item = new (vatpham);
		else
			notify("Đổi thất bại !");
		if (item)
		{
			p = item->move2(who, -1);
			item->add_to_user(p);
			send_user(who, "%c%s", ';', "Bạn đã thành công đổi được " + item->get_name() + ", xin chúc mừng !");
		}
		break;
	}
}
