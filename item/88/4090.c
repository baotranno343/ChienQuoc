
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Phượng Vũ Hài");
        set_picid_1(8808);
        set_picid_2(8808);

        set_level(90);
        set_value(18500);
        set_max_lasting(11499);
        set("dp", 20);
        set("sp", 94);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Phượng Vũ Hài";
}
