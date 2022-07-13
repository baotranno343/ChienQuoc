
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 6; }

// 函数：构造处理
void create()
{
        set_name("Báo Vân Yêu Đới");
        set_picid_1(8705);
        set_picid_2(8705);

        set_level(55);
        set_value(16750);
        set_max_lasting(6399);
        set("dp", 40);
        set("pp", 55);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Báo Vân Yêu Đới";
}
