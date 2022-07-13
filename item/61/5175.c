
// 自动生成：/make/equip/60b
#include <ansi.h>
#include <equip.h>
#include <level.h>
#include <item.h>
#include <effect.h>
#include <skill.h>

inherit ARMOR;

int get_family() { return 5; }
// 函数：构造处理
void create()
{
        set_name("Bá Vương Chiến Bào");
        set_picid_1(6182);        set_picid_2(6182);

        set_level(150);        set_value(78500);
        set_max_lasting(50099);             set("time_item", 1);
        set("dp+", 500);
        set("pp+", 500);
		set("hp+", 1000);
		set("hp%+", 10);
		set("mp%+", 10);
		set("mp+", 1000);
		set("-*%", 10);
		set("sp+", 300);
		//set_item_color(2);

        setup();

        set_gender(2);
        set_armor_code(F_BEIZI);
}

// 函数：获取描述
string get_desc()
{
        object item = this_object();
		if (item->get_lock_time()==0) item->set_lock_time(time()+20*24*60*60);
		return "Bá Vương Chiến Bào";
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