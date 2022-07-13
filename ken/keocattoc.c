#include <ansi.h>
inherit ITEM;
inherit COMBINED;

int get_item_value() { return 500; }
int get_item_value_2() { return 500; }
int get_item_color() { return 3; }

// 函数：构造处理
void create()
{
	set_name("Kéo Cắt Tóc");
	set_picid_1(3513);
	set_picid_2(3513);
	set_value(1);
	set_amount(1);
	set_save("knb", 500);
}
int is_usable() { return 1; }
// 函数：获取描述
string get_desc()
{
	return "Sau khi sử dụng bạn sẽ xuống tóc, quy y cửa phật.";
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
	who->set_hair(99999);
	who->add_to_scene(get_z(who), get_x(who), get_y(who), get_d(who));
	return 0;
}
