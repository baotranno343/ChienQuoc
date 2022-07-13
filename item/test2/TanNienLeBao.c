#include <ansi.h>
inherit ITEM;
inherit COMBINED;

int get_item_value() { return 50; }
int get_item_value_2() { return 50; }
int get_item_color() { return 2; }

// 函数：构造处理
void create()
{
	set_name("Tân Niên Lễ Bao");
	set_picid_1(4981);
	set_picid_2(4981);
	set_value(1);
	set_amount(1);
}
int is_usable() { return 1; }
// 函数：获取描述
string get_desc()
{
	return "Lễ bao chúc phúc, có thể mở ra rất nhiều bảo vật quý hiếm. ";
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
	rate = random(8000);

	if (rate < 2000) //战国令
	{
		item = new ("item/final/15/1525");
		if (!item)
			return 0;
	}
	else if (rate < 3000) //战国号角
	{
		item = new ("item/final/15/1528");
		if (!item)
			return 0;
	}
	else if (rate < 4000) //战国号角
	{
		item = new ("item/final/15/1527");
		if (!item)
			return 0;
	}
	else if (rate < 5000) //战国号角
	{
		item = new ("item/final/15/1529");
		if (!item)
			return 0;
	}
	else if (rate < 6000) //战国号角
	{
		item = new ("item/final/15/1524");
		if (!item)
			return 0;
	}
	else if (rate < 7000) //战国号角
	{
		item = new ("item/final/15/1526");
		if (!item)
			return 0;
	}
	else //乾坤袋
	{
		item = new ("item/91/9167");
		if (!item)
			return 0;
	}
	gift->add_amount(-1);
	if (item)
	{
		send_user(who, "%c%s", '!', "Bạn nhận được " + item->get_name());
		p = item->move2(who);
		item->add_to_user(p);
		//	USER_D->user_channel(sprintf("Bằng hữu "HIR "%s "NOR "mở Đại Lễ Bao nhận được "HIY "%s "NOR ".", who->get_name(),item->get_name() ));
	}
	return 0;
}
