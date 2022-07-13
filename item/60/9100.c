
// 自动生成：/make/equip/60b

#include <equip.h>
#include <effect.h>
#include <skill.h>

inherit ARMOR;

// 函数：适用门派
//int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Hoàng Kim Thánh Y");
        set_picid_1(6042);
        set_picid_2(6042);

        set_level(120);
        set_value(60000);
        set_max_lasting(42799);
        set("dp+", 305);
        set("pp+", 265);
		set("sp+", 165);

        setup();

        set_gender(1);
        set_armor_code(8);
		set_armor_color_1(0x00FFFFE0);
        set_armor_color_2(0x00FFFFE0);
}

// 函数：获取描述
string get_desc()
{
        return "Hoàng Kim Thánh Y";
}