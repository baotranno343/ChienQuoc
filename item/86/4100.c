
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Huyền Kim Hạng Liên");
        set_picid_1(8605);
        set_picid_2(8605);

        set_level(100);
        set_value(69250);
        set_max_lasting(7899);
        set("cp", 0);
        set("pp", 102);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Huyền Kim Hạng Liên";
}
