
#include <equip.h>

inherit ARMOR;

// 函数：构造处理
void create()
{
        set_name("冰魄战甲");
        set_picid_1(6142);
        set_picid_2(6142);
        set_unit("件");

        set_level(0);
        set_value(0);
        set_max_lasting(1099);
        set("dp", 22);
        set("pp", 20);

        setup();

        set_gender(2);
        set_armor_code(F_ZHANJIA);
        set_armor_color_1(0x73f0842e);
        set_armor_color_2(0x00004208);
}

// 函数：获取描述
string get_desc()
{
        return "冰魄战甲";
}
