
#include <equip.h>

inherit HEAD;

// 函数：构造处理
void create()
{
        set_name("Hiệp Sĩ Mạo");
        set_picid_1(6503);
        set_picid_2(6503);
        set_unit("顶");

        set_level(40);
        set_value(3800);
        set_max_lasting(6099);
        set("dp", 17);
        set("pp", 17);
        set("hp", 25);
        set("mp", 25);

        setup();

        set_gender(1);
        set_head_code(M_WUSHENGMAO);
        set_head_color(0x420828c2);
}

// 函数：获取描述
string get_desc()
{
        return "Hiệp Sĩ Mạo";
}
