
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Cản Nhật Hài");
        set_picid_1(8809);
        set_picid_2(8809);

        set_level(50);
        set_value(8500);
        set_max_lasting(7899);
        set("dp", 12);
        set("sp", 46);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Cản Nhật Hài";
}
