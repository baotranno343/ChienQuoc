
#include <equip.h>

inherit HEAD;

// 函数：构造处理
void create()
{
        set_name("Tế Ma Mão");
        set_picid_1(6610);
        set_picid_2(6610);
        set_unit("顶");

        set_level(10);
        set_value(1350);
        set_max_lasting(3699);
        set("dp", 8);
        set("pp", 8);
        set("hp", 10);
        set("mp", 10);

        setup();

        set_gender(2);
        set_head_code(F_PINGMAO);
        set_head_color(0x4208716a);
}

// 函数：获取描述
string get_desc()
{
        return "Tế Ma Mão";
}
