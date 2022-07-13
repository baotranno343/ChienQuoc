
#include <equip.h>

inherit HEAD;

// 函数：构造处理
void create()
{
        set_name("Phu Tử Quán");
        set_picid_1(6525);
        set_picid_2(6525);
        set_unit("顶");

        set_level(50);
        set_value(5500);
        set_max_lasting(7299);
        set("dp", 20);
        set("pp", 20);
        set("hp", 30);
        set("mp", 30);

        setup();

        set_gender(1);
        set_head_code(M_PINGMAO);
        set_head_color(0x42081802);
}

// 函数：获取描述
string get_desc()
{
        return "Phu Tử Quán";
}
