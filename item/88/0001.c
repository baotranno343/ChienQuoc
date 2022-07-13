
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;
//int get_item_color() { return 1; }
// 函数：适用门派
int get_family() { return 8; }

// 函数：构造处理
void create()
{
        set_name("Thảo Hài");
        set_picid_1(8800);
        set_picid_2(8800);

        set_level(0);
        set_value(300);
        set_max_lasting(2199);
        set("dp", 2);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thảo Hài";
}
