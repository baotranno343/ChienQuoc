
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Huyền Ma Hài");
        set_picid_1(8809);
        set_picid_2(8809);

        set_level(55);
        set_value(9700);
        set_max_lasting(8299);
        set("dp", 13);
        set("sp", 52);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Huyền Ma Hài";
}
