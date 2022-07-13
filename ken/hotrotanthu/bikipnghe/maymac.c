#include <ansi.h>
#include <skill.h>
#include <equip.h>
#include <effect.h>
inherit ITEM;
inherit USABLE;
inherit COMBINED;

int get_item_value() { return 1020; }
int get_item_value_2() { return 1020; }
int get_item_color() { return 2; }

// 函数：构造处理
void create()
{
	set_name("Bí Kíp May Mặc");
	set_picid_1(0089);
	set_picid_2(0089);
	set_value(10);
	set_amount(1);
}

// 函数：获取描述
string get_desc()
{
	return "Sử dụng sẽ nhận max cấp kĩ năng May Mặc.";
}

int get_use_effect(object me)
{
	return __FILE__->get_use_effect_callout(me, this_object());
}

int get_use_effect_callout(object who, object gift)
{
	int p;
	object item;

	who->set_skill(0640, 100);
	//	send_user(who,"%c%s",';',"Bạn nhận được "HIY "100000 Kim Nguyên Bảo");
	//	log_file("sdknb.txt", sprintf("%s : %s (%d) %s sử dụng 5 Kim Bảo\n", short_time(time()), who->get_name(), who->get_number(), who->get_id() ));
	gift->add_amount(-1);
	return 0;
}