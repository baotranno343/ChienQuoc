
#include <equip.h>

inherit HEAD;

// 函数：构造处理
void create()
{
        set_name("Tế Miên Mão");
        set_picid_1(6600);
        set_picid_2(6600);
        set_unit("顶");

        set_level(20);
        set_value(1800);
        set_max_lasting(4299);
        set("dp", 11);
        set("pp", 11);
        set("hp", 15);
        set("mp", 15);

        setup();

        set_gender(2);
        set_head_code(F_PINGMAO);
        set_head_color(0x4208226d);
}

// 函数：获取描述
string get_desc()
{
        return "Tế Miên Mão";
}
