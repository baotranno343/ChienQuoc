
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Hồng Bảo Thạch Hạng Liên");
        set_picid_1(8612);
        set_picid_2(8612);

        set_level(90);
        set_value(55500);
        set_max_lasting(8799);
        set("cp", 0);
        set("pp", 90);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Hồng Bảo Thạch Hạng Liên";
}
