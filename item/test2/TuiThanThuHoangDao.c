#include <ansi.h>
inherit ITEM;
inherit COMBINED;

int get_item_value() { return 350; }
int get_item_value_2() { return 350; }
int get_item_color() { return 2; }

// 函数：构造处理
void create()
{
	set_name("Túi Thần Thú Hoàng Đạo");
	set_picid_1(9993);
	set_picid_2(9993);
	set_value(1);
	set_amount(1);
}
int is_usable() { return 1; }
// 函数：获取描述
string get_desc()
{
	return "Mở túi có thể nhận được các Bảo Thú đặc biệt trong 12 cung Hoàng đạo.";
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

	if (rate < 2000) //战国令
	{
		item = new ("item/08/0818");
		if (!item)
			return 0;
	}
	else if (rate < 3000) //战国号角
	{
		item = new ("item/08/0817");
		if (!item)
			return 0;
	}
	else if (rate < 4000) //血石
	{
		item = new ("item/08/0814");
		if (!item)
			return 0;
	}
	else if (rate < 4500) //血石
	{
		item = new ("item/08/0819");
		if (!item)
			return 0;
	}
	else if (rate < 5000) //法力石
	{
		item = new ("item/08/0823");
		if (!item)
			return 0;
	}
	else if (rate < 5500) //法力石
	{
		item = new ("item/08/0813");
		if (!item)
			return 0;
	}
	else if (rate < 6000) //百宝囊
	{
		item = new ("item/08/0820");
		if (!item)
			return 0;
	}
	else if (rate < 6500) //百宝囊
	{
		item = new ("item/08/0821");
		if (!item)
			return 0;
	}
	else if (rate < 7000) //百宝囊
	{
		item = new ("item/08/0822");
		if (!item)
			return 0;
	}
	else if (rate < 7500) //百宝囊
	{
		item = new ("item/08/0816");
		if (!item)
			return 0;
	}
	else if (rate < 8500) //百宝囊
	{
		item = new ("item/08/0815");
		if (!item)
			return 0;
	}
	else //乾坤袋
	{
		item = new ("item/08/0812");
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
		USER_D->user_channel(sprintf("Bằng hữu " HIY "%s " NOR "mở Túi Thần Thú Hoàng Đạo nhận được " HIY "%s " NOR ".", who->get_name(), item->get_name()));
	}
	return 0;
}
