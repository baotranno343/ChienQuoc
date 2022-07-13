#include <ansi.h>
inherit ITEM;
inherit COMBINED;

int get_item_value() { return 150; }
int get_item_value_2() { return 150; }
int get_item_color() { return 2; }

// 函数：构造处理
void create()
{
	set_name("Túi Linh Thạch");
	set_picid_1(7108);
	set_picid_2(7108);
	set_value(1);
	set_amount(1);
}
int is_usable() { return 1; }
// 函数：获取描述
string get_desc()
{
	return "Mở ra sẽ nhận được ngẫu nhiên Linh Thạch từ cấp 1 đến cấp 3";
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

	if (rate < 3) //战国号角
	{
		item = new (sprintf("/item/93/%d", 9301 + random(10)));
		item->set_level(1);
		if (!item)
			return 0;
	}
	else if (rate < 5) //战国号角
	{
		item = new (sprintf("/item/93/%d", 9301 + random(10)));
		item->set_level(2);
		if (!item)
			return 0;
	}
	else //乾坤袋
	{
		item = new (sprintf("/item/93/%d", 9301 + random(10)));
		item->set_level(3);
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
		USER_D->user_channel(sprintf("Bằng hữu " HIR "%s " NOR "mở Túi Linh Thạch nhận được " HIY "%s " NOR ".", who->get_name(), item->get_name()));
	}
	return 0;
}
