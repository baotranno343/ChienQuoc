
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Ngọc Lộ Hạng Liên");
        set_picid_1(8652);
        set_picid_2(8652);

        set_level(60);
        set_value(34500);
        set_max_lasting(7899);
        set("cp", 0);
        set("pp", 65);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Ngọc Lộ Hạng Liên";
}
