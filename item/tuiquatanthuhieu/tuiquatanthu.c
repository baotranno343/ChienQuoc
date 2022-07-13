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
	set_name("Túi Quà Tân Thủ");
	set_picid_1(3106);
	set_picid_2(3106);
	set_level(10);
	set_value(5000);
	set_no_give(1);
	set_no_sell(1);
	set_no_drop(1);
}

// 函数：获取描述
string get_desc(object me)
{
	return "Túi quà hỗ trợ tân thủ tham gia Chiến Quốc.\n Sau khi sử dụng sẽ nhận được :\n" HIC " Túi Hoàng Kim Tân Thủ (Cấp 20)\n 5000 ngân lượng\n Pháp Bảo Cửu Long Thần Hóa Trảo\nSơ Trị Dược\nSơ Phục Dược\n";
}

int get_use_effect(object me)
{
	return __FILE__->get_use_effect_callout(me, this_object());
}

int get_use_effect_callout(object who, object gift)
{
	int gender, family, type, i, q;
	object item5;
	string cTmp, cFile, p;
	gender = who->get_gender() == 1 ? 1 : 2;
	if (who->get_level() < 10)
	{
		send_user(who, "%c%s", '!', "Cấp 10 có thể sử dụng.");
		return 0;
	}
	if (USER_INVENTORY_D->get_free_count(who) < 4)
	{
		send_user(who, "%c%s", '!', "Hành trang không đủ chỗ.");
		return 0;
	}
	gift->remove_from_user();
	//    TASK_LEGEND_D->check_task_item5(who,"Túi Quà Tân Thủ",1);
	destruct(gift);
	who->add_cash(5000);

	item5 = new ("item/test/tuihoangkimtanthucap20");
	q = item5->move2(who, -1);
	item5->set_no_give(1);
	item5->add_to_user(q);
	send_user(who, "%c%s", ';', "Bạn nhận được " HIR "Túi Hoàng Kim Tân Thủ Cấp 20.");

	item5 = new ("item/mop/9512");
	q = item5->move2(who, -1);
	item5->set_no_give(1);
	item5->add_to_user(q);
	send_user(who, "%c%s", ';', "Bạn nhận được " HIR "Pháp Bảo Cửu Long Thần Hỏa Trảo");

	item5 = new ("item/sell/0007");

	q = item5->move2(who, -1);
	item5->set_amount(5);
	item5->set_no_give(1);
	item5->add_to_user(q);
	send_user(who, "%c%s", ';', "Bạn nhận được " HIR "Sơ Trị Dược");

	item5 = new ("item/sell/0009");
	q = item5->move2(who, -1);
	item5->set_amount(5);
	item5->set_no_give(1);
	item5->add_to_user(q);
	send_user(who, "%c%s", ';', "Bạn nhận được " HIR "Sơ Phục Dược");

	return 0;
}