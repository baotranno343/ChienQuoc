#include <ansi.h>
#include <equip.h>
#include <effect.h>
inherit ITEM;
inherit USABLE;

int get_item_color() { return 2; }
int get_item_value() { return 100; }
int get_item_value_2() { return 100; }

// 函数：构造处理
void create()
{
	set_name("Túi Quà Hỗ Trợ Tân Thủ");
	set_picid_1(3105);
	set_picid_2(3105);
	set_level(10);
	set_value(10000);
	set_no_give(1);
	set_no_sell(1);
	set_no_drop(1);
}

// 函数：获取描述
string get_desc(object me)
{
	return "Túi quà tân thủ Chiến Quốc dành cho người chơi.\n Người chơi sẽ nhận được: " HIC "\n 3 Đại Huyết Thạch \n 3 Pháp Lực Thạch \n 5 Trị Dược \n 5 Phục Dược \n 2 Chiến Quốc Lệnh \n 50.000 Ngân Lượng Khóa";
}

int get_use_effect(object me)
{
	return __FILE__->get_use_effect_callout(me, this_object());
}

int get_use_effect_callout(object me, object gift)
{
	string arg;

	int gender, family, type, i, q;
	object item, item1, item2, item3, item4, item5;
	string cTmp, cFile, p;
	gender = me->get_gender() == 1 ? 1 : 2;
	if (me->get_level() < 10)
	{
		send_user(me, "%c%s", '!', "Cấp 10 có thể sử dụng.");
		return 0;
	}
	if (USER_INVENTORY_D->get_free_count(me) < 7)
	{
		send_user(me, "%c%s", '!', "Hành trang không đủ chỗ.");
		return 0;
	}
	gift->remove_from_user();
	destruct(gift);

	item = new ("item/08/0006");
	item->set_amount(2);
	q = item->move2(me, -1);
	item->add_to_user(q);
	item->set_no_give(1);
	item = new ("item/sell/0002");
	item->set_amount(3);
	q = item->move2(me, -1);
	item->add_to_user(q);
	item->set_no_give(1);

	item = new ("item/sell/0004");
	item->set_amount(3);
	q = item->move2(me, -1);
	item->add_to_user(q);
	item->set_no_give(1);

	item = new ("item/sell/0008");
	item->set_amount(5);
	q = item->move2(me, -1);
	item->add_to_user(q);
	item->set_no_give(1);

	item = new ("item/sell/0010");
	item->set_amount(5);
	q = item->move2(me, -1);
	item->add_to_user(q);
	item->set_no_give(1);

	return 0;
}
