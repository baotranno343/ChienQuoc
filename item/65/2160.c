
// 自动生成：/make/equip/60b

#include <equip.h>
#include <level.h>
#include <item.h>

inherit HEAD;

int get_family() { return 2; }
// 函数：构造处理
void create()
{
        set_name("Bá Vương Quỷ Quán");
        set_picid_1(6562);        set_picid_2(6562);

        set_level(150);        set_value(56500);
        set_max_lasting(50099);
        set("dp+", 270);
        set("pp+", 270);
		set("hp+", 500);
		set("hp%+", 5);
		set("mp+", 550);
		set("mp%+", 5);
		set("-c*%", 10);
		set("sp+", 200);
	//	set_item_color(2);

        setup();

        set_gender(1);
        set_head_code(48);
}

// 函数：获取描述
string get_desc()
{
        return "Bá Vương Quỷ Quán";
}