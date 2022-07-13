
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 5; }

// 函数：构造处理
void create()
{
        set_name("Thị Thiên Hài");
        set_picid_1(8810);
        set_picid_2(8810);

        set_level(70);
        set_value(18000);
        set_max_lasting(6999);
        set("dp", 16);
        set("sp", 27);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thị Thiên Hài";
}
