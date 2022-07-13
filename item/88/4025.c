
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Thanh Vân Hài");
        set_picid_1(8805);
        set_picid_2(8805);

        set_level(25);
        set_value(2300);
        set_max_lasting(5599);
        set("dp", 7);
        set("sp", 16);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thanh Vân Hài";
}
