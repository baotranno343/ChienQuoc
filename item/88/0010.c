
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 8; }

// 函数：构造处理
void create()
{
        set_name("Bố Hài");
        set_picid_1(8800);
        set_picid_2(8800);

        set_level(10);
        set_value(1400);
        set_max_lasting(4899);
        set("dp", 4);
        set("sp", 4);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Bố Hài";
}
