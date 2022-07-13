#include <ansi.h>
inherit ITEM;
inherit COMBINED;

int get_item_value() { return 50; }
int get_item_value_2() { return 50; }
int get_item_color() { return 2; }

// 函数：构造处理
void create()
{
	set_name("Túi Hàng");
	set_picid_1(4981);
	set_picid_2(4981);
	set_value(10);
	set_amount(1);
}
int is_usable() { return 1; }
// 函数：获取描述
string get_desc()
{
	return "Mở ra sẽ nhận được các phần thưởng bất ngờ.";
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

	rate = random(100);

	// if (rate < 2)
	// 	item = new ("item/sell/5032");

	else if (rate < 30)
	{
		"sys/sys/test_db"->add_yuanbao(who, 50);
		send_user(who, "%c%s", '!', "Bạn nhận được 5knb");
	}

	else if (rate < 60)
	{
		who->add_cash(40000);
		send_user(who, "%c%s", '!', "Bạn nhận được 40k Ngân Lượng ");
	}
	else //乾坤袋
	{
		who->add_exp(100000);
		send_user(who, "%c%s", '!', "Bạn nhận được 100000 EXP ");
	}
	gift->add_amount(-1);
	if (item)
	{
		send_user(who, "%c%s", '!', "Bạn nhận được " + item->get_name());
		p = item->move2(who);
		item->add_to_user(p);
		USER_D->user_channel(sprintf("Bằng hữu " HIR "%s " NOR "mở Túi Hàng nhận được " HIY "%s " NOR ".", who->get_name(), item->get_name()));
	}
	return 0;
}
