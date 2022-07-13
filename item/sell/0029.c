
#include <equip.h>
#include <effect.h>

inherit TALISMAN;

int get_item_value() { return 90; }
int get_item_value_2() { return 90; }
int get_item_number() { return 10001024; }
int get_item_color() { return 1; }

int get_no_repair() { return 1; }

// 函数：法宝识别
int get_talisman_type() { return 13; }

//不是完成任务时不掉耐久度
int add_lasting(int time)
{
	if (time < 0 && time > -100)
		return 0;
	return ::add_lasting(time);
}
int add_potential(int pot, object who)
{
	int i;
	object item = this_object();
	if (who->get_online_rate() != 100)
		return 0;
	pot = pot * 3 / 10;
	if (add_lasting(-100) <= 0)
	{
		send_user(who, "%c%s", '!', sprintf("%s của ngươi vỡ vụn,  không thể sử dụng được nữa", get_name()));
		item->remove_from_user();
		destruct(item);
	}
	return pot;
}
// 函数：构造处理
void create()
{
	object me = this_object();

	set_name("Thượng Phương Bảo Kiếm");
	set_picid_1(7208);
	set_picid_2(7208);
	set_value(10);
	//	set_save("knb2",50);
	set_level(1);
	set_max_lasting(2099);

	setup();
}

string get_short()
{
	return "Mỗi lần Hoàn thành nhiệm vụ của Sư Gia được thưởng gấp 1.3 Tiềm Năng. Có thể sử dụng 20 lần.";
}

// 函数：获取描述
string get_desc()
{
	return "Ngự Ban cho Bảo Kiếm\Mỗi lần hoàn thành nhiệm vụ của Sư Gia được thưởng gấp 1.3 tiềm năng\n(Mỗi lần tiêu hao 1 độ bền)";
}
