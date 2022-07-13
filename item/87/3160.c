
// 自动生成：/make/equip/60b

#include <equip.h>
#include <level.h>
#include <item.h>

inherit WAIST;

int get_family() { return 3; }
// 函数：构造处理
void create()
{
        set_name("Hoả Lân Yêu Đới");
        set_picid_1(8704);        set_picid_2(8704);

        set_level(150);        set_value(39500);
        set_max_lasting(50099);
        set("dp+", 150);
        set("pp+", 150);
		set("hp+", 1500);
		set("mp+", 1500);
		set("hp%+", 30);
		set("mp%+", 30);
		set("sp+", 150);
	//	//set_item_color(2);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Hoả Lân Yêu Đới";
}