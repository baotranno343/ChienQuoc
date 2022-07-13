
#include <equip.h>

inherit ARMOR;

// 函数：构造处理
void create()
{
        set_name("短褂");
        set_picid_1(5000);
        set_picid_2(5000);
        set_unit("件");

        set_level(0);
        set_value(1);
        set_max_lasting(900);
        set("dp", 10);
        set("pp", 10);
        set("hp", 5);
        set("mp", 5);

        setup();

        set_gender(1);
        set_armor_code(M_DUANGUA);
        set_armor_color_1( H_YELLOW | H_RED_H );
        set_armor_color_2( H_BLACK | H_BLACK_H );
}

// 函数：获取描述
string get_desc()
{
        return "男性装备";
}
