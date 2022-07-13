#include <ansi.h>
#include <equip.h>

inherit "/inh/equip/fashion";
;

int get_item_value() { return 200; }
int get_item_value_2() { return 200; }
int get_item_color() { return 2; }
int is_tieuhuy() { return 2; }
// 函数：构造处理
void create()
{
	set_name("Xích Y (Nữ)");
	set_picid_1(11056);
	set_picid_2(11056);

	set_level(1);
	set_bind(1);
	set_value(500);
	set_max_lasting(35099);

	set("time_item", 1);

	set("dp", 50);
	set("pp", 50);
	set("hp", 100);

	setup();

	set_gender(2);

	set_fashion_code(56);
}

// 函数：获取描述
string get_desc()
{
	return "Loại trang phục cho nữ giới thường gặp.";
}

// 函数：使用效果
int get_equip_effect(object me)
{
	return __FILE__->get_equip_effect_callout(me, this_object());
}

// 函数：使用效果(在线更新)
int get_equip_effect_callout(object me, object item)
{
	//处理时间控制上面的。
	if (item->get_lock_time() == 0)
	{
		item->set_lock_time(time() + 14 * 24 * 60 * 60);
		send_user(me, "%c%d%c", 0x31, getoid(item), 0);
	}
}

//
string get_tail_desc()
{
	object item = this_object();
	string desc;

	if (item->get_lock_time() == 0)
	{
		desc = HIG "(Chưa kích hoạt)" NOR "[Thời gian sử dụng 14 ngày]\n ";
	}

	return desc;
}
