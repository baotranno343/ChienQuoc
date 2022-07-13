#include <ansi.h>
#include <equip.h>
#include <effect.h>
inherit ITEM;
inherit COMBINED;
inherit USABLE;

int get_max_combined() { return 10000; }
int get_item_color() { return 2; }
int get_item_value() { return 1000; }
int get_item_value_2() { return 1000; }

// 函数：构造处理
void create()
{
	set_name("Chén Ngân Lượng Khóa");
	set_picid_1(3507);
	set_picid_2(3507);
	set_level(10);
	set_value(1000);
	set_no_give(1);
	set_no_sell(1);
	set_no_drop(1);
	set_amount(1);
}

// 函数：获取描述
string get_desc(object me)
{
	return "Sử dụng sẽ nhận được 1 triệu ngân lượng";
}

int get_use_effect(object me)
{
	return __FILE__->get_use_effect_callout(me, this_object());
}

int get_use_effect_callout(object who, object gift)
{
	int gender, family, exp, type;
	object item, item1;
	string cTmp, cFile, p;
	if (who->get_save_2("chuyensinh.score"))
	{
		send_user(who, "%c%s", '!', "Chuyển Sinh Không Thể Sử Dụng Chén Bạc.");
		return 0;
	}
	if (who->get_level() < 10)
	{
		send_user(who, "%c%s", '!', "Cấp 10 mới có thể sử dụng.");
		return 0;
	}
	//		TASK_LEGEND_D->check_task_item1(who,"Chén Bạc VIP",1);
	if (who->get_cashkhoa() > 10000000)
	{
		send_user(who, "%c%s", '!', "Ngân Lượng Khóa của bạn đã đạt 10.000.000");
		return 0;
	}
	who->add_cashkhoa(1000000);
	gift->add_amount(-1);
}