
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Kì Lân Hài");
        set_picid_1(8805);
        set_picid_2(8805);

        set_level(90);
        set_value(21500);
        set_max_lasting(11199);
        set("dp", 43);
        set("sp", 48);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Kì Lân Hài";
}
