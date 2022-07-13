#include <ansi.h>
inherit ITEM;
inherit COMBINED;

int get_item_value() { return 400; }
int get_item_value_2() { return 400; }
int get_item_color() { return 2; }

// 函数：构造处理
void create()
{
	set_name("Thẻ Giảm Giá");
	set_picid_1(3812);
	set_picid_2(3812);
	set_value(1000);
	set_amount(1);
}
int is_usable() { return 1; }
// 函数：获取描述
string get_desc()
{
	return "Sử dụng khi tái tạo vũ khí hoặc trang bị, \nsau khi sử dụng sẽ giảm 50% số ngân lượng cần cho 20 lần tái tạo.";
}

int get_use_effect(object me)
{
	return __FILE__->get_use_effect_callout(me, this_object());
}

int get_use_effect_callout(object who, object gift)
{
	send_user(who, "%c%s", ';', sprintf("Bạn bây giờ có %d cơ hội Giảm 50%% số ngân lượng khi tái tạo.", who->get_save("giamtientaitao") + 20));
	who->add_save("giamtientaitao", 20);
	gift->add_amount(-1);
	return 0;
}