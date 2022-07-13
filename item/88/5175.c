
// 自动生成：/make/equip/60b

#include <ansi.h>
#include <equip.h>
#include <level.h>
#include <item.h>
#include <effect.h>
#include <skill.h>

inherit BOOTS;

int get_family() { return 5; }
// 函数：构造处理
void create()
{
        set_name("Sát Thần Phụng Lữ");
        set_picid_1(8813);        set_picid_2(8813);

        set_level(150);        set_value(35500);
        set_max_lasting(50099);
        set("time_item", 1);
		set("dp+", 200);
		set("pp+", 200);
		set("hp+", 325);
		set("mp+", 355);
		set("hp*", 1);
		set("mp*", 1);
		set("hp+@", 100);
		set("mp+@", 200);
        set("sp+", 440);
		//set_item_color(2);

        setup();
}

// 函数：获取描述
string get_desc()
{
        object item = this_object();
		if (item->get_lock_time()==0) item->set_lock_time(time()+20*24*60*60);
		return "Sát Thần Phụng Lữ";
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