
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Thần Hành Yêu Đới");
        set_picid_1(8714);
        set_picid_2(8714);

        set_level(55);
        set_value(11250);
        set_max_lasting(9799);
        set("dp", 55);
        set("pp", 40);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thần Hành Yêu Đới";
}
