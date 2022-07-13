
// 自动生成：/make/equip/60b

#include <equip.h>
#include <level.h>
#include <item.h>

inherit BOOTS;

int get_family() { return 1; }
// 函数：构造处理
void create()
{
        set_name("Sát Thần Phụng Lữ");
        set_picid_1(8813);        set_picid_2(8813);

        set_level(150);        set_value(35500);
        set_max_lasting(50099);
        set("dp+", 140);
		set("pp+", 140);
		set("hp+", 325);
		set("mp+", 355);
		set("hp*", 1);
		set("mp*", 1);
		set("hp+@", 100);
	//	set("mp+@", 200);
		set("yuan+@",1);
        set("sp+", 440);
		//set_item_color(2);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Sát Thần Phụng Lữ";
}