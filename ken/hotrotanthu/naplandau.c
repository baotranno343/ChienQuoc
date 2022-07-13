#include <ansi.h>
#include <equip.h>
#include <effect.h>
inherit ITEM;
inherit USABLE;

int get_item_color() { return 1; }
int get_item_value() { return 100; }
int get_item_value_2() { return 100; }

// 函数：构造处理
void create()
{
	set_name("Túi Quà Nạp Lần Đầu");
	set_picid_1(4981);
	set_picid_2(4981);
	set_level(10);
	set_value(10000);
	set_no_give(1);
	set_no_sell(1);
	set_no_drop(1);
}

// 函数：获取描述
string get_desc(object me)
{
	return "Túi quà tặng Chiến Quốc dành cho người chơi nạp Kim Nguyên Bảo lần đầu.\n Người chơi sẽ nhận được: " HIC "\n 5 Đại Huyết Thạch \n 5 Pháp Lực Thạch \n 10 Trị Dược \n 10 Phục Dược \n 20 Hồi Thành Phù \n Đấu Chiến Gấm Y hoặc Xích Y\n Túi Bách Bảo \n 3 Chiến Quốc Lệnh \n 50.000 Ngân Lượng Khóa";
}

int get_use_effect(object me)
{
	return __FILE__->get_use_effect_callout(me, this_object());
}

int get_use_effect_callout(object who, object gift)
{
	int gender, family, type, i, n, q;
	object item;
	string cTmp, cFile, p;
	gender = who->get_gender() == 1 ? 1 : 2;
	if (who->get_level() < 10)
	{
		send_user(who, "%c%s", '!', "Cấp 10 có thể sử dụng.");
		return 0;
	}
	if (USER_INVENTORY_D->get_free_count(who) < 10)
	{
		send_user(who, "%c%s", '!', "Hành trang không đủ chỗ.");
		return 0;
	}
	gift->remove_from_user();
	destruct(gift);

	who->add_cashkhoa(50000);
	item = new ("item/sell/0002");
	item->set_amount(5);
	n = item->move2(who, -1);
	item->add_to_user(n);
	item->set_no_give(1);

	item = new ("item/sell/0004");
	item->set_amount(5);
	q = item->move2(who, -1);
	item->add_to_user(q);
	item->set_no_give(1);

	item = new ("item/sell/0008");
	item->set_amount(10);
	q = item->move2(who, -1);
	item->add_to_user(q);
	item->set_no_give(1);

	item = new ("item/sell/0010");
	item->set_amount(10);
	q = item->move2(who, -1);
	item->add_to_user(q);
	item->set_no_give(1);

	item = new ("item/std/0407");
	item->set_amount(20);
	q = item->move2(who, -1);
	item->add_to_user(q);
	item->set_no_give(1);

	item = new ("item/std/6006");
	q = item->move2(who, -1);
	item->add_to_user(q);
	item->set_no_give(1);

	item = new ("item/08/0006");
	item->set_amount(3);
	q = item->move2(who, -1);
	item->add_to_user(q);
	item->set_no_give(1);

	if (gender == 1)
	{
		item = new ("item/100/10056");
		q = item->move2(who, -1);
		item->add_to_user(q);
		item->set_no_give(1);
	}
	else
	{
		item = new ("item/100/11056");
		q = item->move2(who, -1);
		item->add_to_user(q);
		item->set_no_give(1);
	}
}