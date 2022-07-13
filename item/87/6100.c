
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 6; }

// 函数：构造处理
void create()
{
        set_name("Vân Long Yêu Đới");
        set_picid_1(8714);
        set_picid_2(8714);

        set_level(100);
        set_value(32500);
        set_max_lasting(7699);
        set("dp", 85);
        set("pp", 100);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Vân Long Yêu Đới";
}
