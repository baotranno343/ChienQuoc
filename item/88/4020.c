
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Tùy Phong Hài");
        set_picid_1(8805);
        set_picid_2(8805);

        set_level(20);
        set_value(1100);
        set_max_lasting(5199);
        set("dp", 6);
        set("sp", 10);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Tùy Phong Hài";
}
