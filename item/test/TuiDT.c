#include <ansi.h>
inherit ITEM;
inherit COMBINED;

int get_item_value() { return 200; }
int get_item_value_2() { return 200; }
int get_item_color() { return 2; }

// 函数：构造处理
void create()
{
	set_name("Túi Đoạn Thạch");
	set_picid_1(7106);
	set_picid_2(7106);
	set_value(10);
	set_amount(1);
}
int is_usable() { return 1; }
// 函数：获取描述
string get_desc()
{
	return "Mở túi có thể nhận được ngẫu nhiên các loại Đoạn Thạch.";
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
	rate = random(6);

	if (rate == 0 || rate == 1 || rate == 2) // SC
	{
		item = new ("/item/sell/0032");
		if (!item)
			return 0;
	}

	else if (rate == 3 || rate == 4) // TC
	{
		item = new ("/item/sell/1032");
		if (!item)
			return 0;
	}
	else if (rate == 5) // CC
	{
		item = new ("/item/sell/2032");
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
		//USER_D->user_channel(sprintf("Bằng hữu "HIY"%s "NOR "mở Túi Đoạn Thạch "HIY"%s "NOR ".", who->get_name(),item->get_name() ));
	}
	return 0;
}
