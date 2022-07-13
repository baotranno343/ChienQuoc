
// 自动生成：/make/equip/60b

#include <equip.h>

inherit ARMOR;

// 函数：构造处理
void create()
{
        set_name("%s");
        set_picid_1(%d);
        set_picid_2(%d);
        set_unit("%s");

        set_level(%d);
        set_value(%d);
        set_max_lasting(%d);
        set("dp", %d);
        set("pp", %d);
        set("hp", %d);
        set("mp", %d);

        setup();

        set_gender(1);
        set_armor_code(%s);
        set_armor_color_1(0x%04x%04x);
        set_armor_color_2(0x%04x%04x);
}

// 函数：获取描述
string get_desc()
{
        return "%s";
}
