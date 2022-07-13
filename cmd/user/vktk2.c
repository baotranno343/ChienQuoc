#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>

int main(object me, string arg)
{

	int skill = to_int(arg), p, check_give;
	string result;
	object item, item1;

	if (!objectp(item1 = present("Túi Nguyên Liệu Thần Binh", me, 1, MAX_CARRY * 4)))
	{
		write_user(me, ECHO "Bạn không có Túi Nguyên Liệu Thần Binh !");
		return 1;
	}
	if (USER_INVENTORY_D->get_free_count(me) < 1)
	{
		write_user(me, ECHO "Hành trang của bạn không đủ 1 chỗ trống!");
		return 1;
	}
	check_give = item1->get_no_give();
	if (arg == 0)
	{
		result = sprintf("Bạn đang sử dụng Túi Nguyên Liệu Thần Binh, xin hãy lựa chọn :\n");
		result += ESC "Thạch Điêu Quyền Nhẫn\nvktk2 1\n";
		result += ESC "Nguyệt Hoàn\nvktk2 2\n";
		result += ESC "Kim Đao\nvktk2 3\n";
		result += ESC "Ngọc Kiếm\nvktk2 4\n";
		result += ESC "Xích Anh Thương\nvktk2 5\n";
		result += ESC "Cổ Phương Côn\nvktk2 6\n";
		result += ESC "Hủy bỏ\n";
		send_user(me, "%c%s", ':', result);
		return 1;
	}
	if (arg == "1")
	{
		item = new ("/item/70/1075");
		item->set_no_give(check_give);
		item->set_hide(0);
		p = item->move2(me, -1);
		item->add_to_user(p);
		item1->remove_from_user();
		destruct(item1);
		send_user(me, "%c%s", ';', "Bạn nhận được " HIY "Thạch Điêu Quyền Nhẫn");
		return 1;
	}
	if (arg == "2")
	{
		item = new ("/item/71/1075");
		item->set_no_give(check_give);
		item->set_hide(0);
		p = item->move2(me, -1);
		item->add_to_user(p);
		item1->remove_from_user();
		destruct(item1);
		send_user(me, "%c%s", ';', "Bạn nhận được " HIY "Nguyệt Hoàn");
		return 1;
	}
	if (arg == "3")
	{
		item = new ("/item/72/1075");
		item->set_no_give(check_give);
		item->set_hide(0);
		p = item->move2(me, -1);
		item->add_to_user(p);
		item1->remove_from_user();
		destruct(item1);
		send_user(me, "%c%s", ';', "Bạn nhận được " HIY "Kim Đao");
		return 1;
	}
	if (arg == "4")
	{
		item = new ("/item/73/1075");
		item->set_no_give(check_give);
		item->set_hide(0);
		p = item->move2(me, -1);
		item->add_to_user(p);
		item1->remove_from_user();
		destruct(item1);
		send_user(me, "%c%s", ';', "Bạn nhận được " HIY "Ngọc Kiếm");
		return 1;
	}
	if (arg == "5")
	{
		item = new ("/item/74/1075");
		item->set_no_give(check_give);
		item->set_hide(0);
		p = item->move2(me, -1);
		item->add_to_user(p);
		item1->remove_from_user();
		destruct(item1);
		send_user(me, "%c%s", ';', "Bạn nhận được " HIY "Xích Anh Thương");
		return 1;
	}
	if (arg == "6")
	{
		item = new ("/item/75/1075");
		item->set_no_give(check_give);
		item->set_hide(0);
		p = item->move2(me, -1);
		item->add_to_user(p);
		item1->remove_from_user();
		destruct(item1);
		send_user(me, "%c%s", ';', "Bạn nhận được " HIY "Cổ Phương Côn");
		return 1;
	}
	return 1;
}