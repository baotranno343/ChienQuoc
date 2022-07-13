#include <ansi.h>
#include <effect.h>
#include <skill.h>
#include <time.h>
#include <equip.h>

inherit TALISMAN;
int get_talisman_type() { return 1; }

int get_item_color() {return 3 ;}

// 函数：构造处理
void create()
{
		set_name("Nhẫn Tình Nhân");
		set_picid_1(8614); // picid không đúng
		set_picid_2(8614); // picid không đúng
		set_value(200);
		set_max_lasting(35099);

		set("time_item",1);

		set("ap", 200);
		set("dp", 200);
		set("cp", 200);
		set("hp", 300);

		setup();
}   

// 函数：获取描述
string get_desc() 
{
	return "Nhẫn Tây Thi tặng";
}

// 函数：使用效果
int get_equip_effect( object me )
{
	return __FILE__ ->get_equip_effect_callout(me, this_object());
}

// 函数：使用效果(在线更新)
int get_equip_effect_callout( object me, object item )
{
	//处理时间控制上面的。
	if (item->get_lock_time() == 0)
	{
		item->set_lock_time(time()+14*24*60*60);
		send_user( me, "%c%d%c", 0x31, getoid(item), 0 );
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