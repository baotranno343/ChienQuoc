
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 6; }

// 函数：构造处理
void create()
{
        set_name("Sí Diễm Hạng Liên");
        set_picid_1(8655);
        set_picid_2(8655);

        set_level(100);
        set_value(80000);
        set_max_lasting(6099);
        set("cp", 190);
        set("pp", 105);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Sí Diễm Hạng Liên";
}
