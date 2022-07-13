
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Ngọc Long Hạng Liên");
        set_picid_1(8652);
        set_picid_2(8652);

        set_level(90);
        set_value(55500);
        set_max_lasting(8799);
        set("cp", 0);
        set("pp", 85);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Ngọc Long Hạng Liên";
}
