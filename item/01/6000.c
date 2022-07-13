
#include <equip.h>

inherit ARMOR;

// 函数：构造处理
void create()
{
        set_name("男装布衣");
        set_picid_1(6000);
        set_picid_2(6000);
        set_unit("件");

        set_level(0);
        set_value(40);
        set_max_lasting(2599);
        set("dp", 10);

        setup();

        set_gender(1);
        set_armor_code(M_BUYI);
        set_armor_color_1(0x51c44a48);
        set_armor_color_2(0x00001881);
}

// 函数：获取描述
string get_desc()
{
        return "一种适合男孩穿戴的初学者防具。";
}
