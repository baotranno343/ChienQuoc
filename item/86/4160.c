
// 自动生成：/make/equip/60b

#include <equip.h>
#include <level.h>
#include <item.h>

inherit NECK;

int get_family() { return 4; }
// 函数：构造处理
void create()
{
        set_name("Linh Quy Quỷ Liên");
        set_picid_1(8614);        set_picid_2(8614);

        set_level(150);        set_value(98000);
        set_max_lasting(50099);
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
        return "Linh Quy Quỷ Liên";
}