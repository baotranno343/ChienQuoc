
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 6; }

// 函数：构造处理
void create()
{
        set_name("Phi Long Yêu Đới");
        set_picid_1(8714);
        set_picid_2(8714);

        set_level(90);
        set_value(29000);
        set_max_lasting(7399);
        set("dp", 75);
        set("pp", 90);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Phi Long Yêu Đới";
}
