
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 6; }

// 函数：构造处理
void create()
{
        set_name("Long Đầu Hài");
        set_picid_1(8805);
        set_picid_2(8805);

        set_level(50);
        set_value(11000);
        set_max_lasting(6099);
        set("dp", 12);
        set("sp", 19);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Long Đầu Hài";
}
