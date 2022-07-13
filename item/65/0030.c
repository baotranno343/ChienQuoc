
#include <equip.h>

inherit HEAD;

// 函数：构造处理
void create()
{
        set_name("Vũ Sinh Mạo");
        set_picid_1(6503);
        set_picid_2(6503);
        set_unit("顶");

        set_level(30);
        set_value(2400);
        set_max_lasting(4899);
        set("dp", 14);
        set("pp", 14);
        set("hp", 20);
        set("mp", 20);

        setup();

        set_gender(1);
        set_head_code(M_WUSHENGMAO);
        set_head_color(0x420828c2);
}

// 函数：获取描述
string get_desc()
{
        return "Vũ Sinh Mạo";
}
