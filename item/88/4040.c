
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Lý Ngư Hài");
        set_picid_1(8805);
        set_picid_2(8805);

        set_level(40);
        set_value(6000);
        set_max_lasting(6999);
        set("dp", 10);
        set("sp", 34);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Lý Ngư Hài";
}
