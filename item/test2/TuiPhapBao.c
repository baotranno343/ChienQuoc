#include <ansi.h>
inherit ITEM;
inherit COMBINED;

int get_item_value() { return 100; }
int get_item_value_2() { return 100; }
int get_item_color() { return 2; }

// 函数：构造处理
void create()
{
	set_name("Túi Pháp Bảo");
	set_picid_1(3107);
	set_picid_2(3107);
	set_value(10);
	set_amount(1);
}
int is_usable() { return 1; }
// 函数：获取描述
string get_desc()
{
	return "Túi thần kỳ, có thể mở ra rất nhiều loại Pháp Bảo và vật phẩm đáng giá";
}

int get_use_effect(object me)
{
	return __FILE__->get_use_effect_callout(me, this_object());
}

int get_use_effect_callout(object who, object gift)
{
	int rate, p, cash, check_give;
	object item;

	if (USER_INVENTORY_D->get_free_count(who) < 1)
	{
		notify("Hành trang không đủ 1 chỗ trống");
		return 0;
	}
	rate = random(100);
	check_give = gift->get_no_give();

	if (rate < 5) //战国令
	{
		item = new ("item/30/3036");
		if (!item)
			return 0;
	}
	else if (rate < 10) //法力石
	{
		item = new ("item/30/3034");
		if (!item)
			return 0;
	}
	else if (rate < 20) //战国号角
	{
		item = new ("item/mop/9522");
		if (!item)
			return 0;
	}
	else if (rate < 30) //血石
	{
		item = new ("item/mop/9512");
		if (!item)
			return 0;
	}
	else if (rate < 40) //法力石
	{
		item = new ("item/mop/9532");
		if (!item)
			return 0;
	}
	else if (rate < 45) //法力石
	{
		item = new ("item/30/3024");
		if (!item)
			return 0;
	}
	else if (rate < 50) //法力石
	{
		item = new ("item/30/3024f");
		if (!item)
			return 0;
	}
	else if (rate < 60) //法力石
	{
		item = new ("item/30/3027");
		if (!item)
			return 0;
	}

	else if (rate < 65)
	{
		item = new ("/item/100/10056");
		if (!item)
			return 0;
	}
	else if (rate < 70)
	{
		item = new ("/item/100/11056");
		if (!item)
			return 0;
	}
	else if (rate < 75) //乾坤袋
	{
		item = new ("item/mop/9552");
		if (!item)
			return 0;
	}
	else if (rate < 85) //乾坤袋
	{
		item = new ("item/mop/9562");
		if (!item)
			return 0;
	}
	else if (rate < 90) //法力石
	{
		item = new (sprintf("item/%d/1075", 70 + random(6)));
		if (!item)
			return 0;
	}
	else if (rate < 95)
	{
		item = new ("item/sell/0032");
		if (!item)
			return 0;
	}
	else if (rate < 98)
	{
		item = new ("item/sell/1032"); //Trung Cấp đoạn thạch
		if (!item)
			return 0;
	}
	else
	{
		item = new ("item/sell/2032"); //Cao Cấp đoạn thạch
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
		USER_D->user_channel(sprintf("Bằng hữu %s mở Túi Pháp Bảo nhận được %s ", who->get_name(), item->get_name()));
	}
	return 0;
}
