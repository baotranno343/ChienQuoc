
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 6; }

// 函数：构造处理
void create()
{
        set_name("Vân Long Hài");
        set_picid_1(8810);
        set_picid_2(8810);

        set_level(100);
        set_value(28500);
        set_max_lasting(8299);
        set("dp", 22);
        set("sp", 39);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Vân Long Hài";
}
