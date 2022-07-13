
#include <equip.h>

inherit ARMOR;

// 函数：构造处理
void create()
{
        set_name("女装布衣");
        set_picid_1(6100);
        set_picid_2(6100);
        set_unit("件");

        set_level(0);
        set_value(40);
        set_max_lasting(2599);
        set("dp", 10);

        setup();

        set_gender(2);
        set_armor_code(F_BUYI);
        set_armor_color_1(0x10e41988);
        set_armor_color_2(0x000010a3);
}

// 函数：获取描述
string get_desc()
{
        return "一种适合女孩穿戴的初学者防具。";
}
