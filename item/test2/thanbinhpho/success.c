#include <ansi.h>
#include <task.h>
inherit ITEM;
inherit COMBINED;

int get_item_value() { return 50; }
int get_item_value_2() { return 50; }
int get_item_color() { return 2; }

// 函数：构造处理
void create()
{
	set_name("Tìm kiếm thần binh");
	set_picid_1(3107);
	set_picid_2(3107);
	set_value(1);
	set_amount(1);
}
int is_usable() { return 1; }
// 函数：获取描述
string get_desc()
{
	return "Tiêu diệt 10000 quái vật, BOSS.";
}

int get_use_effect(object me)
{
	return __FILE__->get_use_effect_callout(me, this_object());
}

int get_use_effect_callout(object who, object gift)
{
	int rate, p, cash;
	object item, item1, item2, item3;

	gift->add_amount(-1);
	who->set_save_2("cantuong.count", 10000);
	who->set_save_2("cantuong.hv", 1);
	who->set_save_2("cantuong.agbd", 1);
	who->set_save_2("cantuong.uvdtq", 1);
	who->set_save_2("cantuong.ktl", 1);
	send_user(who, "%c%c%c%w%w%s", 0x51, 1, 2, TID_CANTUONG, 1, "Tìm kiếm Thần Binh Phổ(Hoàn thành)");
	return 0;
}
