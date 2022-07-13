
// 自动生成：/make/equip/60b

#include <ansi.h>
#include <equip.h>
#include <level.h>
#include <item.h>
#include <effect.h>
#include <skill.h>

inherit NECK;

int get_family() { return 4; }
// 函数：构造处理
void create()
{
        set_name("Linh Quy Quỷ Liên");
        set_picid_1(8614);        set_picid_2(8614);

        set_level(150);        set_value(98000);
        set_max_lasting(50099);             set("time_item", 1);
        set("time_item", 1);
		set("ap+", 300);
	//	set("cp+", 300);
	//	set("cp%+", 5);
		set("ap%+", 5);
		set("dp+", 100);
        set("pp+", 100);
		set("sp+", 100);
		//set_item_color(2);

        setup();
}

// 函数：获取描述
string get_desc()
{
        object item = this_object();
		if (item->get_lock_time()==0) item->set_lock_time(time()+20*24*60*60);
		return "Linh Quy Quỷ Liên";
}
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
		item->set_lock_time(time()+20*24*60*60);
		send_user( me, "%c%d%c", 0x31, getoid(item), 0 );
	}
}