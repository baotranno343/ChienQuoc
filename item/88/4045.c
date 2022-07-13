
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Truy Vân Hài");
        set_picid_1(8805);
        set_picid_2(8805);

        set_level(45);
        set_value(7300);
        set_max_lasting(7399);
        set("dp", 11);
        set("sp", 40);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Truy Vân Hài";
}
