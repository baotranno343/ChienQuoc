
#include <npc.h>
#include <ansi.h>
#include <equip.h>

inherit OFFICER;

// 函数：获取人物造型
int get_char_picid() { return 8267; }
int is_seller() { return 1; }
int is_self_look() { return 1; }
void do_gift(string arg);

// 函数：构造处理
void create()
{
	set_name("Hỗ Trợ Chiến Quốc");

	set_2("talk", (["gift":(
							   : do_gift:),
	]));

	setup();
}

void do_look(object who)
{
	int id = getoid(this_object());
	send_user(who, "%c%c%w%s", ':', 3, get_char_picid(), sprintf(" %s :\n Ta có thể giúp gì cho ngươi?\n"
																 //ESC "Nhận Chén Bạc\ntalk %x# gift.1\n"
																 ESC "Nhận Phi Phong Và Cánh\ntalk %x# gift.2\n" ESC "Nhận Bảo Thú Tiểu Hỏa Sư\ntalk %x# gift.3\n"
																 //ESC "Nhận Huyễn Thú\ntalk %x# gift.4\n"
																 ESC "Nhận Pháp Bảo\ntalk %x# gift.5\n" ESC "Nhận Kỹ Năng Bang\ntalk %x# gift.6\n" ESC "Nhận Thần Binh\ntalk %x# gift.7\n" ESC "Nhận Huyết Sắc\ntalk %x# gift.8\n"
																 //ESC "Nhận Kỹ Năng Chế Đồ\ntalk %x# gift.9\n"
																 //	ESC "Nhận KNB Khóa\ntalk %x# gift.10\n"
																 ESC "Rời khỏi",
																 get_name(), id, id, id, id, id, id, id, id, id, id, id, id, id, id));
}

void do_gift(string arg)
{
	object me = this_object();
	__FILE__->do_gift2(me, arg);
}

void do_gift2(object me, string arg)
{
	int flag, id, i, p;
	object who, item;
	string *nTmp, cFile;

	who = this_player();
	id = getoid(me);
	flag = to_int(arg);
	who->set_time("talk", 0);
	if (who->get_level() < 10)
	{
		send_user(who, "%c%s", '!', "LV 10 trở lên mới có thể nhận hỗ trợ.");
		return 0;
	}
	switch (flag)
	{
	/*case 1:
		if (who->get_save_2("hotro.chenbac"))
		{
			send_user(who, "%c%s", '!', "Bạn đã nhận hỗ trợ chén bạc rồi.");
			return 0;
		}
		if (USER_INVENTORY_D->count_empty_carry(who) < 1)
		{
			send_user(who, "%c%s", '!', "Bạn phải có ít nhất 1 ô trống trong hành trang!");
			return 0;
		}
		item = new ("item/test/chenbacvip");
		item->set_amount(30);
		p = item->move2(who, -1);
		item->add_to_user(p);
		who->set_save_2("hotro.chenbac", 1);
		send_user(who, "%c%s", '!', "Bạn nhận được 30 Chén Bạc");
		break;*/
	case 2:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf(me->get_name() + ":\n" + "Phi Phong Và Cánh\n" ESC "Phi Phong Nam\ntalk %x# gift.20\n" ESC "Phi Phong Nữ\ntalk %x# gift.21\n" ESC "Cánh Nam\ntalk %x# gift.22\n" ESC "Cánh Nữ\ntalk %x# gift.23\n" ESC "Thoát ra\nCLOSE\n", id, id, id, id, id));
		break;
	case 20:
		if (who->get_save_2("hotro.ppvacanh"))
		{
			send_user(who, "%c%s", '!', "Bạn đã nhận hỗ trợ Phi Phong Nam rồi.");
			return 0;
		}
		if (USER_INVENTORY_D->count_empty_carry(who) < 1)
		{
			send_user(who, "%c%s", '!', "Bạn phải có ít nhất 1 ô trống trong hành trang!");
			return 0;
		}
		item = new ("item/ppvacanh/vgpp");
		p = item->move2(who, -1);
		item->add_to_user(p);
		who->set_save_2("hotro.ppvacanh", 1);
		send_user(who, "%c%s", '!', "Bạn nhận được Phi Phong Nam");
		break;
	case 21:
		if (who->get_save_2("hotro.ppvacanh"))
		{
			send_user(who, "%c%s", '!', "Bạn đã nhận hỗ trợ Phi Phong Nữ rồi.");
			return 0;
		}
		if (USER_INVENTORY_D->count_empty_carry(who) < 1)
		{
			send_user(who, "%c%s", '!', "Bạn phải có ít nhất 1 ô trống trong hành trang!");
			return 0;
		}
		item = new ("item/ppvacanh/xnpp");

		p = item->move2(who, -1);
		item->add_to_user(p);
		who->set_save_2("hotro.ppvacanh", 1);
		send_user(who, "%c%s", '!', "Bạn nhận được Phi Phong Nữ");
		break;
	case 22:
		if (who->get_save_2("hotro.ppvacanh"))
		{
			send_user(who, "%c%s", '!', "Bạn đã nhận hỗ trợ Cánh Nam rồi.");
			return 0;
		}
		if (USER_INVENTORY_D->count_empty_carry(who) < 1)
		{
			send_user(who, "%c%s", '!', "Bạn phải có ít nhất 1 ô trống trong hành trang!");
			return 0;
		}
		item = new ("item/ppvacanh/canhnam");

		p = item->move2(who, -1);
		item->add_to_user(p);
		who->set_save_2("hotro.ppvacanh", 1);
		send_user(who, "%c%s", '!', "Bạn nhận được Cánh Nam");
		break;
	case 23:
		if (who->get_save_2("hotro.ppvacanh"))
		{
			send_user(who, "%c%s", '!', "Bạn đã nhận hỗ trợ Cánh Nữ rồi.");
			return 0;
		}
		if (USER_INVENTORY_D->count_empty_carry(who) < 1)
		{
			send_user(who, "%c%s", '!', "Bạn phải có ít nhất 1 ô trống trong hành trang!");
			return 0;
		}
		item = new ("item/ppvacanh/canhnu");

		p = item->move2(who, -1);
		item->add_to_user(p);
		who->set_save_2("hotro.ppvacanh", 1);
		send_user(who, "%c%s", '!', "Bạn nhận được Cánh Nữ");
		break;
	case 3:
		if (who->get_save_2("hotro.tieuhoasu"))
		{
			send_user(who, "%c%s", '!', "Bạn đã nhận hỗ trợ Tiểu Hỏa Sư rồi.");
			return 0;
		}
		if (USER_INVENTORY_D->count_empty_carry(who) < 1)
		{
			send_user(who, "%c%s", '!', "Bạn phải có ít nhất 1 ô trống trong hành trang!");
			return 0;
		}
		item = new ("item/08/1002");
		item->set_no_give(1);
		p = item->move2(who, -1);
		item->add_to_user(p);
		who->set_save_2("hotro.tieuhoasu", 1);
		send_user(who, "%c%s", '!', "Bạn nhận được Tiểu Hỏa Sư");
		break;
	/*case 4:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf(me->get_name() + ":\n" + "Huyễn Thú\n" ESC "Hắc Hỏa Sư - Công\ntalk %x# gift.40\n" ESC "Hỏa Sư - Thủ\ntalk %x# gift.41\n" ESC "Thoát ra\nCLOSE\n", id, id, id, id, id));
		break;
	case 40:
		if (who->get_save_2("hotro.huyenthu"))
		{
			send_user(who, "%c%s", '!', "Bạn đã nhận hỗ trợ Huyễn Thú rồi.");
			return 0;
		}
		if (USER_INVENTORY_D->count_empty_carry(who) < 1)
		{
			send_user(who, "%c%s", '!', "Bạn phải có ít nhất 1 ô trống trong hành trang!");
			return 0;
		}
		item = new ("item/huyenthu/hachoasu");
		item->set_no_give(1);
		p = item->move2(who, -1);
		item->add_to_user(p);
		who->set_save_2("hotro.huyenthu", 1);
		send_user(who, "%c%s", '!', "Bạn nhận được Huyễn Thú - Hắc Hỏa Sư");
		break;
	case 41:
		if (who->get_save_2("hotro.huyenthu"))
		{
			send_user(who, "%c%s", '!', "Bạn đã nhận hỗ trợ Huyễn Thú rồi.");
			return 0;
		}
		if (USER_INVENTORY_D->count_empty_carry(who) < 1)
		{
			send_user(who, "%c%s", '!', "Bạn phải có ít nhất 1 ô trống trong hành trang!");
			return 0;
		}
		item = new ("item/huyenthu/hoasu");
		item->set_no_give(1);
		p = item->move2(who, -1);
		item->add_to_user(p);
		who->set_save_2("hotro.huyenthu", 1);
		send_user(who, "%c%s", '!', "Bạn nhận được Huyễn Thú - Hắc Hỏa Sư");
		break;*/
	case 5:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf(me->get_name() + ":\n" + "Pháp Bảo Vip\n" ESC "Chân Long Tử Ấn Ngoại\ntalk %x# gift.50\n" ESC "Chân Long Tử Ấn Nội\ntalk %x# gift.51\n" ESC "Thoát ra\nCLOSE\n", id, id, id, id, id));
		break;
	case 50:
		if (who->get_save_2("hotro.phapbao"))
		{
			send_user(who, "%c%s", '!', "Bạn đã nhận hỗ trợ Pháp Bảo rồi.");
			return 0;
		}
		if (USER_INVENTORY_D->count_empty_carry(who) < 1)
		{
			send_user(who, "%c%s", '!', "Bạn phải có ít nhất 1 ô trống trong hành trang!");
			return 0;
		}
		item = new ("item/phapbaovip/ngoai");
		item->set_no_give(1);
		p = item->move2(who, -1);
		item->add_to_user(p);
		who->set_save_2("hotro.phapbao", 1);
		send_user(who, "%c%s", '!', "Bạn nhận được Pháp Bảo Ngoại");
		break;
	case 51:
		if (who->get_save_2("hotro.phapbao"))
		{
			send_user(who, "%c%s", '!', "Bạn đã nhận hỗ trợ Pháp Bảo rồi.");
			return 0;
		}
		if (USER_INVENTORY_D->count_empty_carry(who) < 1)
		{
			send_user(who, "%c%s", '!', "Bạn phải có ít nhất 1 ô trống trong hành trang!");
			return 0;
		}
		item = new ("item/phapbaovip/noi");
		item->set_no_give(1);
		p = item->move2(who, -1);
		item->add_to_user(p);
		who->set_save_2("hotro.phapbao", 1);
		send_user(who, "%c%s", '!', "Bạn nhận được Pháp Bảo Nội");
		break;
	case 6:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf(me->get_name() + ":\n" + "Kỹ Năng Bang\n" ESC "Kỹ Năng Bang Ngoại Công\ntalk %x# gift.60\n" ESC "Kỹ Năng Bang Nội Công\ntalk %x# gift.61\n" ESC "Kỹ Năng Bang Đường Môn\ntalk %x# gift.62\n" ESC "Thoát ra\nCLOSE\n", id, id, id, id, id));
		break;
	case 60:
		if (who->get_save_2("hotro.kynangbang"))
		{
			send_user(who, "%c%s", '!', "Bạn đã nhận hỗ trợ Kỹ Năng Bang rồi.");
			return 0;
		}
		if (USER_INVENTORY_D->count_empty_carry(who) < 1)
		{
			send_user(who, "%c%s", '!', "Bạn phải có ít nhất 1 ô trống trong hành trang!");
			return 0;
		}
		item = new ("ken/hotrotanthu/kynangbangngoaicong");
		item->set_no_give(1);
		p = item->move2(who, -1);
		item->add_to_user(p);
		who->set_save_2("hotro.kynangbang", 1);
		send_user(who, "%c%s", '!', "Bạn nhận được Kỹ Năng Bang Ngoại");
		break;
	case 61:
		if (who->get_save_2("hotro.kynangbang"))
		{
			send_user(who, "%c%s", '!', "Bạn đã nhận hỗ trợ Kỹ Năng Bang rồi.");
			return 0;
		}
		if (USER_INVENTORY_D->count_empty_carry(who) < 1)
		{
			send_user(who, "%c%s", '!', "Bạn phải có ít nhất 1 ô trống trong hành trang!");
			return 0;
		}
		item = new ("ken/hotrotanthu/kynangbangnoicong");
		item->set_no_give(1);
		p = item->move2(who, -1);
		item->add_to_user(p);
		who->set_save_2("hotro.kynangbang", 1);
		send_user(who, "%c%s", '!', "Bạn nhận được Kỹ Năng Bang Nội");
		break;
	case 62:
		if (who->get_save_2("hotro.kynangbang"))
		{
			send_user(who, "%c%s", '!', "Bạn đã nhận hỗ trợ Kỹ Năng Bang rồi.");
			return 0;
		}
		if (USER_INVENTORY_D->count_empty_carry(who) < 1)
		{
			send_user(who, "%c%s", '!', "Bạn phải có ít nhất 1 ô trống trong hành trang!");
			return 0;
		}
		item = new ("ken/hotrotanthu/kynangbangduongmon");
		item->set_no_give(1);
		p = item->move2(who, -1);
		item->add_to_user(p);
		who->set_save_2("hotro.kynangbang", 1);
		send_user(who, "%c%s", '!', "Bạn nhận được Kỹ Năng Bang Đường Môn");
		break;

	case 7:
		send_user(who, "%c%c%w%s", ':', 3, me->get_char_picid(), sprintf(me->get_name() + ":\n" + "Thần Binh\n" ESC "Quyền Thủ\ntalk %x# gift.70\n" ESC "Kiếm\ntalk %x# gift.71\n" ESC "Đao\ntalk %x# gift.72\n" ESC "Thương\ntalk %x# gift.73\n" ESC "Bổng\ntalk %x# gift.74\n" ESC "Ám Khí\ntalk %x# gift.75\n" ESC "Thoát ra\nCLOSE\n", id, id, id, id, id, id, id, id, id));
		break;
	case 70:
		if (who->get_save_2("hotro.thanbinh"))
		{
			send_user(who, "%c%s", '!', "Bạn đã nhận hỗ trợ Thần Binh rồi.");
			return 0;
		}
		if (USER_INVENTORY_D->count_empty_carry(who) < 1)
		{
			send_user(who, "%c%s", '!', "Bạn phải có ít nhất 1 ô trống trong hành trang!");
			return 0;
		}
		item = new ("item/70/9130");
		item->set_no_give(1);
		p = item->move2(who, -1);
		item->add_to_user(p);
		who->set_save_2("hotro.thanbinh", 1);
		send_user(who, "%c%s", '!', "Bạn nhận được Thần Binh Quyền Thủ");
		break;
	case 71:
		if (who->get_save_2("hotro.thanbinh"))
		{
			send_user(who, "%c%s", '!', "Bạn đã nhận hỗ trợ Thần Binh rồi.");
			return 0;
		}
		if (USER_INVENTORY_D->count_empty_carry(who) < 1)
		{
			send_user(who, "%c%s", '!', "Bạn phải có ít nhất 1 ô trống trong hành trang!");
			return 0;
		}
		item = new ("item/73/9130");
		item->set_no_give(1);
		p = item->move2(who, -1);
		item->add_to_user(p);
		who->set_save_2("hotro.thanbinh", 1);
		send_user(who, "%c%s", '!', "Bạn nhận được Thần Binh Kiếm");
		break;
	case 72:
		if (who->get_save_2("hotro.thanbinh"))
		{
			send_user(who, "%c%s", '!', "Bạn đã nhận hỗ trợ Thần Binh.");
			return 0;
		}
		if (USER_INVENTORY_D->count_empty_carry(who) < 1)
		{
			send_user(who, "%c%s", '!', "Bạn phải có ít nhất 1 ô trống trong hành trang!");
			return 0;
		}
		item = new ("item/72/9130");
		item->set_no_give(1);
		p = item->move2(who, -1);
		item->add_to_user(p);
		who->set_save_2("hotro.thanbinh", 1);
		send_user(who, "%c%s", '!', "Bạn nhận được Thần Binh Đao");
		break;
	case 73:
		if (who->get_save_2("hotro.thanbinh"))
		{
			send_user(who, "%c%s", '!', "Bạn đã nhận hỗ trợ Thần Binh rồi.");
			return 0;
		}
		if (USER_INVENTORY_D->count_empty_carry(who) < 1)
		{
			send_user(who, "%c%s", '!', "Bạn phải có ít nhất 1 ô trống trong hành trang!");
			return 0;
		}
		item = new ("item/74/9130");
		item->set_no_give(1);
		p = item->move2(who, -1);
		item->add_to_user(p);
		who->set_save_2("hotro.thanbinh", 1);
		send_user(who, "%c%s", '!', "Bạn nhận được Thần Binh Thương");
		break;
	case 74:
		if (who->get_save_2("hotro.thanbinh"))
		{
			send_user(who, "%c%s", '!', "Bạn đã nhận hỗ trợ Thần Binh rồi.");
			return 0;
		}
		if (USER_INVENTORY_D->count_empty_carry(who) < 1)
		{
			send_user(who, "%c%s", '!', "Bạn phải có ít nhất 1 ô trống trong hành trang!");
			return 0;
		}
		item = new ("item/75/9130");
		item->set_no_give(1);
		p = item->move2(who, -1);
		item->add_to_user(p);
		who->set_save_2("hotro.thanbinh", 1);
		send_user(who, "%c%s", '!', "Bạn nhận được Thần Binh Bổng");
		break;
	case 75:
		if (who->get_save_2("hotro.thanbinh"))
		{
			send_user(who, "%c%s", '!', "Bạn đã nhận hỗ trợ Thần Binh rồi.");
			return 0;
		}
		if (USER_INVENTORY_D->count_empty_carry(who) < 1)
		{
			send_user(who, "%c%s", '!', "Bạn phải có ít nhất 1 ô trống trong hành trang!");
			return 0;
		}
		item = new ("item/71/9130");
		item->set_no_give(1);
		p = item->move2(who, -1);
		item->add_to_user(p);
		who->set_save_2("hotro.thanbinh", 1);
		send_user(who, "%c%s", '!', "Bạn nhận được Thần Binh Ám Khí");
		break;
	case 8:
		if (who->get_save_2("hotro.huyetsac"))
		{
			send_user(who, "%c%s", '!', "Bạn đã nhận hỗ trợ Huyết Sắc rồi.");
			return 0;
		}
		if (USER_INVENTORY_D->count_empty_carry(who) < 1)
		{
			send_user(who, "%c%s", '!', "Bạn phải có ít nhất 1 ô trống trong hành trang!");
			return 0;
		}
		item = new ("ken/hotrotanthu/tuihuyetsac");
		//	item->set_no_give(1);
		p = item->move2(who, -1);
		item->add_to_user(p);
		who->set_save_2("hotro.huyetsac", 1);
		send_user(who, "%c%s", '!', "Bạn nhận được Huyết Sắc");
		break;
		/*case 9:
		if (who->get_save_2("hotro.kynangsong"))
		{
			send_user(who, "%c%s", '!', "Bạn đã nhận hỗ trợ Kỹ Năng Sống rồi.");
			return 0;
		}
		if (USER_INVENTORY_D->count_empty_carry(who) < 6)
		{
			send_user(who, "%c%s", '!', "Bạn phải có ít nhất 6 ô trống trong hành trang!");
			return 0;
		}
		item = new ("ken/hotrotanthu/bikipnghe/coquan");
		item->set_no_give(1);
		p = item->move2(who, -1);
		item->add_to_user(p);
		item = new ("ken/hotrotanthu/bikipnghe/daubep");
		item->set_no_give(1);
		p = item->move2(who, -1);
		item->add_to_user(p);
		item = new ("ken/hotrotanthu/bikipnghe/dieukhac");
		item->set_no_give(1);
		p = item->move2(who, -1);
		item->add_to_user(p);
		item = new ("ken/hotrotanthu/bikipnghe/luyendon");
		item->set_no_give(1);
		p = item->move2(who, -1);
		item->add_to_user(p);
		item = new ("ken/hotrotanthu/bikipnghe/maymac");
		item->set_no_give(1);
		p = item->move2(who, -1);
		item->add_to_user(p);
		item = new ("ken/hotrotanthu/bikipnghe/renduc");
		item->set_no_give(1);
		p = item->move2(who, -1);
		item->add_to_user(p);
		who->set_save_2("hotro.kynangsong", 1);
		send_user(who, "%c%s", '!', "Bạn nhận được Kỹ Năng Sống Cơ Quan");
		break;
	case 10:
		if (who->get_save_2("hotro.knbkhoa"))
		{
			send_user(who, "%c%s", '!', "Bạn đã nhận hỗ trợ KNB Khóa rồi.");
			return 0;
		}
		who->add_save("knbkhoa", 10000);
		who->set_save_2("hotro.knbkhoa", 1);
		send_user(who, "%c%s", '!', "Bạn nhận được 1000 KNB");
		break;*/
	}
}
