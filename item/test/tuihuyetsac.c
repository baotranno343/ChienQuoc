#include <ansi.h>
#include <effect.h>
inherit ITEM;
inherit USABLE;

int get_item_color() { return 2; }
int get_item_value() { return 30000; }
int get_item_value_2() { return 30000; }

// 函数：构造处理
void create()
{
	set_name("Túi Trang Bị Huyết Sắc");
	set_picid_1(7125);
	set_picid_2(7125);
	set_value(10000);
}

// 函数：获取描述
string get_desc()
{
	return "Sử dụng sẽ nhận được một bộ Trang bị Huyết Sắc cấp 105 tương ứng môn phái.";
}

int get_use_effect(object me)
{
	return __FILE__->get_use_effect_callout(me, this_object());
}

int get_use_effect_callout(object who, object gift)
{
	int p;
	object item;

	if (who->get_fam_name() == "")
	{
		send_user(who, "%c%s", '!', "Gia Nhập Phái đi Bạn.");
		return 0;
	}
	if (USER_INVENTORY_D->get_free_count(who) < 5)
	{
		notify("Hành trang không đủ 5 chỗ trống");
		return 0;
	}
	gift->remove_from_user();
	destruct(gift);
	item = new (sprintf("item/huyetlong/%d/%s", who->get_fam_type(), "non"));
	item->set_hide(0);
	p = item->move2(who, -1);
	item->add_to_user(p);
	item = new (sprintf("item/huyetlong/%d/%s", who->get_fam_type(), "ao"));
	item->set_hide(0);
	p = item->move2(who, -1);
	item->add_to_user(p);
	item = new (sprintf("item/huyetlong/%d/%s", who->get_fam_type(), "hanglien"));
	item->set_hide(0);
	p = item->move2(who, -1);
	item->add_to_user(p);
	item = new (sprintf("item/huyetlong/%d/%s", who->get_fam_type(), "yeudoi"));
	item->set_hide(0);
	p = item->move2(who, -1);
	item->add_to_user(p);
	item = new (sprintf("item/huyetlong/%d/%s", who->get_fam_type(), "giay"));
	item->set_hide(0);
	p = item->move2(who, -1);
	item->add_to_user(p);
	return 0;
}