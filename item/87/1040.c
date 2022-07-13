
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Lục Thanh Yêu Đới");
        set_picid_1(8713);
        set_picid_2(8713);

        set_level(40);
        set_value(7500);
        set_max_lasting(8499);
        set("dp", 40);
        set("pp", 25);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Lục Thanh Yêu Đới";
}
