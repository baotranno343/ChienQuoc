
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Liệu Viêm Hạng Liên");
        set_picid_1(8612);
        set_picid_2(8612);

        set_level(40);
        set_value(22750);
        set_max_lasting(6099);
        set("cp", 0);
        set("pp", 42);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Liệu Viêm Hạng Liên";
}
