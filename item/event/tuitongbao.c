#include <ansi.h>
inherit ITEM;
inherit COMBINED;

int get_item_value() { return 50; }
int get_item_value_2() { return 50; }
int get_item_color() { return 2; }

// 函数：构造处理
void create()
{
	set_name("Túi Tổng Bảo");
	set_picid_1(12412);
	set_picid_2(12412);
	set_value(10);
	set_amount(1);
}
int is_usable() { return 1; }
// 函数：获取描述
string get_desc()
{
	return "Những vật phẩm Tổng Bảo Tiểu Yêu thu thập được đều được cất trong túi.";
}

int get_use_effect(object me)
{
	return __FILE__->get_use_effect_callout(me, this_object());
}

int get_use_effect_callout(object who, object gift)
{
	int rate, p, cash;
	object item;

	if (USER_INVENTORY_D->get_free_count(who) < 1)
	{
		notify("Hành trang không đủ 1 chỗ trống");
		return 0;
	}
	rate = random(10000);
	// if (rate < 200)
	// {
	// 	item = new ("item/sell/5032");
	// 	if (!item)
	// 		return 0;
	// }
	else if (rate < 750)
	{
		item = new ("item/sell/1032");
		if (!item)
			return 0;
	}
	else if (rate < 1500)
	{
		item = new ("item/TuiLinhThach/NgauNhien/2");
		if (!item)
			return 0;
	}
	else if (rate < 3000)
	{
		item = new ("item/TuiLinhThach/NgauNhien/3");
		if (!item)
			return 0;
	}
	else if (rate < 4000)
	{
		item = new ("item/91/9167");
		if (!item)
			return 0;
	}
	else if (rate < 5000)
	{
		item = new ("item/sell/0032");
		if (!item)
			return 0;
	}
	// else if (rate < 5500)
	// {
	// 	item = new ("item/huyenthu/exp");
	// 	if (!item)
	// 		return 0;
	// }
	else
	{
		who->add_cash(30000);
		send_user(who, "%c%s", '!', "Bạn nhận được 50000 lượng.");
	}
	gift->add_amount(-1);
	if (item)
	{
		send_user(who, "%c%s", '!', "Bạn nhận được " + item->get_name());
		p = item->move2(who);
		item->add_to_user(p);
		USER_D->user_channel(sprintf("Bằng hữu " HIR "%s" NOR " mở Túi Tổng Bảo được " HIY "%s" NOR ".", who->get_name(), item->get_name()));
	}
	return 0;
}
