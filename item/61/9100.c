
// 自动生成：/make/equip/60b

#include <equip.h>
#include <effect.h>
#include <skill.h>

inherit ARMOR;

// 函数：适用门派
//int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Hoàng Kim Thánh Bào");
        set_picid_1(6182);
        set_picid_2(6182);

        set_level(120);
        set_value(71500);
        set_max_lasting(37599);
        set("dp+", 305);
        set("pp+", 265);
		set("sp+", 165);

        setup();

        set_gender(2);
        set_armor_code(28);
		set_armor_color_1(0x00FFFFE0);
        set_armor_color_2(0x00FFFFE0);
}

// 函数：获取描述
string get_desc()
{
        return "Hoàng Kim Thánh Bào";
}