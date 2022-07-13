#include <ansi.h>
inherit ITEM;
inherit COMBINED;

int get_item_value() { return 10; }
int get_item_value_2() { return 10; }
int get_item_color() { return 2; }

// 函数：构造处理
void create()
{
	set_name("Ân Xá Phù");
	set_picid_1(0401);
	set_picid_2(0401);
	set_value(1000);
	set_amount(1);
}
int is_usable() { return 1; }
// 函数：获取描述
string get_desc()
{
	return "Sau khi sử dụng sẽ giảm tối đa 100 điểm Ác Danh PK.";
}

int get_use_effect(object me)
{
	return __FILE__->get_use_effect_callout(me, this_object());
}

int get_use_effect_callout(object who, object gift)
{
	if (who->get_pk() <= 0)
	{
		write_user(who, ECHO "Bạn không có điểm PK, không thể sử dụng");
		return 0;
	}
	if (who->get_pk() >= 100)
	{
		who->add_pk(-100);
		send_user(who, "%c%s", '!', "Bạn đã giảm 100 điểm PK");
		who->add_to_scene(get_z(who), get_x(who), get_y(who), get_d(who));
	}
	else if (who->get_pk() < 100)
	{
		send_user(who, "%c%s", '!', sprintf("Bạn đã giảm %d điểm PK", who->get_pk()));
		who->add_pk(-who->get_pk());
		who->add_to_scene(get_z(who), get_x(who), get_y(who), get_d(who));
	}
	gift->add_amount(-1);
	return 0;
}
