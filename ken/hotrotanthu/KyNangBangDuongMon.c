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
	set_name("Kĩ Năng Bang Hội Đường Môn");
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
	return "Kĩ năng bang hội \nSau khi sử dụng tất cả kĩ năng Bang hội phái Đường Môn sẽ đạt cấp 50 và cường hóa đạt 5";
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
	if (who->get_level() < 60)
	{
		send_user(who, "%c%s", ';', sprintf("Cấp bậc nhỏ hơn 60 không thể sử dụng.", who->get_level()));
		write_user(who, sprintf(ECHO "Cấp bậc nhỏ hơn 60 không thể sử dụng.", who->get_level()));
		return 0;
	}
	gender = who->get_gender() == 1 ? 0 : 1;

	gift->remove_from_user();
	destruct(gift);

	who->set_skill(0430, 5);
	who->set_skill(0431, 5);
	who->set_skill(0433, 5);
	who->set_skill(0436, 5);
	who->set_skill(0104, 50);
	who->set_skill(0109, 50);
	who->set_skill(0161, 50);
	who->set_skill(0202, 50);
	who->set_skill(0401, 50);
	who->set_skill(0403, 50);
	who->set_skill(0404, 50);
	who->set_skill(0405, 50);
	send_user(who, "%c%s", ';', "Tất cả kĩ năng " HIR "Bang Hội dành cho Đường Môn " NOR "đã được nâng cấp");
	return 0;
}