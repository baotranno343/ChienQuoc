
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Ngọc Lũ Hài");
        set_picid_1(8803);
        set_picid_2(8803);

        set_level(35);
        set_value(4400);
        set_max_lasting(7099);
        set("dp", 18);
        set("sp", 15);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Ngọc Lũ Hài";
}
