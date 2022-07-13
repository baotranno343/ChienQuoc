
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Phất Hiêu Hài");
        set_picid_1(8807);
        set_picid_2(8807);

        set_level(25);
        set_value(2500);
        set_max_lasting(6299);
        set("dp", 13);
        set("sp", 13);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Phất Hiêu Hài";
}
