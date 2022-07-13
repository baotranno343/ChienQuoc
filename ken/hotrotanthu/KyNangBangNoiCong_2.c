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
	set_name("Kĩ Năng Bang Hội Nội Công");
	set_picid_1(9808);
	set_picid_2(9808);
	set_level(10);
	set_value(50);
	set_no_give(1);
	set_no_sell(1);
	set_no_drop(1);
}

// 函数：获取描述
string get_desc(object me)
{
	return "Kĩ năng bang hội \nSau khi sử dụng tất cả kĩ năng Bang hội sẽ đạt cấp 50 và cường hóa đạt cấp 5";
}

int get_use_effect(object me)
{
	return __FILE__->get_use_effect_callout(me, this_object());
}

int get_use_effect_callout(object who, object gift)
{
	int p, gender, family, type;
	object item;
	string cTmp, cFile;
	gender = who->get_gender() == 1 ? 0 : 1;

	gift->remove_from_user();
	destruct(gift);



	who->set_skill(0109, 113);
	who->set_skill(0131, 83);
	who->set_skill(0202, 100);
	who->set_skill(0401, 50);
	who->set_skill(0402, 50);
	who->set_skill(0403, 107);
	who->set_skill(0404, 50);
	who->set_skill(0405, 80);
	send_user(who, "%c%s", ';', "Tất cả kĩ năng " HIR "Bang Hội dành cho hệ Nội " NOR "đã được nâng cấp");
	return 0;
}