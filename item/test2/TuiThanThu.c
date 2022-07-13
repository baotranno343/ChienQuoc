#include <ansi.h>
inherit ITEM;
inherit COMBINED;

int get_item_value() { return 100; }
int get_item_value_2() { return 100; }
int get_item_color() { return 2; }

// 函数：构造处理
void create()
{
	set_name("Túi Thần Thú");
	set_picid_1(9993);
	set_picid_2(9993);
	set_value(1);
	//	set_save("knb",50);
	set_amount(1);
}
int is_usable() { return 1; }
// 函数：获取描述
string get_desc()
{
	return "Túi quà Thần Thú chứa đựng rất nhiều thần thú và thú cưỡi quý giá";
}

int get_use_effect(object me)
{
	return __FILE__->get_use_effect_callout(me, this_object());
}

int get_use_effect_callout(object who, object gift)
{
	int rate, p, cash, check_give;
	object item;
	check_give = gift->get_no_give();
	if (USER_INVENTORY_D->get_free_count(who) < 1)
	{
		notify("Hành trang không đủ 1 chỗ trống");
		return 0;
	}
	rate = random(10000);

	if (rate < 500) //战国令
	{
		item = new ("item/test2/ThanThuMaYet");
		if (!item)
			return 0;
	}
	else if (rate < 1000) //战国号角
	{
		item = new ("item/08/0850");
		if (!item)
			return 0;
	}
	else if (rate < 2000) //血石
	{
		item = new ("item/08/0851");
		if (!item)
			return 0;
	}
	else if (rate < 3000) //血石
	{
		item = new ("item/08/0852");
		if (!item)
			return 0;
	}
	else if (rate < 4000) //法力石
	{
		item = new ("item/08/0853");
		if (!item)
			return 0;
	}
	else if (rate < 5000) //法力石
	{
		item = new ("item/08/0854");
		if (!item)
			return 0;
	}
	else if (rate < 5500) //百宝囊
	{
		item = new ("item/ride/TuiThanThu/006");
		if (!item)
			return 0;
	}
	else if (rate < 6000) //百宝囊
	{
		item = new ("item/ride/TuiThanThu/004");
		if (!item)
			return 0;
	}
	else if (rate < 6500) //百宝囊
	{
		item = new ("item/ride/TuiThanThu/007");
		if (!item)
			return 0;
	}
	else if (rate < 7000) //百宝囊
	{
		item = new ("item/ride/TuiThanThu/001");
		if (!item)
			return 0;
	}
	else if (rate < 7500) //百宝囊
	{
		item = new ("item/ride/TuiThanThu/003");
		if (!item)
			return 0;
	}
	else if (rate < 8000) //百宝囊
	{
		item = new ("item/ride/TuiThanThu/005");
		if (!item)
			return 0;
	}
	else //乾坤袋
	{
		item = new ("item/ride/TuiThanThu/002");
		if (!item)
			return 0;
	}
	gift->add_amount(-1);
	if (item)
	{
		send_user(who, "%c%s", '!', "Bạn nhận được " + item->get_name());
		item->set_no_give(check_give);
		p = item->move2(who);
		item->add_to_user(p);
		USER_D->user_channel(sprintf("Bằng hữu %s mở Túi Thần Thú nhận được %s ", who->get_name(), item->get_name()));
	}
	return 0;
}
