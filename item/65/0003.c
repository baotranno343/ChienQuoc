
#include <equip.h>

inherit HEAD;

// 函数：构造处理
void create()
{
        set_name("Thô Bố Mạo");
        set_picid_1(6520);
        set_picid_2(6520);
        set_unit("顶");

        set_level(0);
        set_value(950);
        set_max_lasting(2499);
        set("dp", 5);
        set("pp", 5);
        set("hp", 5);
        set("mp", 5);

        setup();

        set_gender(1);
        set_head_code(M_ZHANMAO);
        set_head_color(0x42083942);
}

// 函数：获取描述
string get_desc()
{
        return "Thô Bố Mạo";
}
