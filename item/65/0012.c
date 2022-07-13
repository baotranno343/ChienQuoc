
#include <equip.h>

inherit HEAD;

// 函数：构造处理
void create()
{
        set_name("Thô Ma Mão");
        set_picid_1(6520);
        set_picid_2(6520);
        set_unit("顶");

        set_level(10);
        set_value(1350);
        set_max_lasting(3699);
        set("dp", 8);
        set("pp", 8);
        set("hp", 10);
        set("mp", 10);

        setup();

        set_gender(1);
        set_head_code(M_ZHANMAO);
        set_head_color(0x42083942);
}

// 函数：获取描述
string get_desc()
{
        return "Thô Ma Mão";
}
