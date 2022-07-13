
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Lục Thanh Hài");
        set_picid_1(8803);
        set_picid_2(8803);

        set_level(40);
        set_value(6000);
        set_max_lasting(7399);
        set("dp", 20);
        set("sp", 18);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Lục Thanh Hài";
}
