
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 6; }

// 函数：构造处理
void create()
{
        set_name("Lam Bảo Thạch Hạng Liên");
        set_picid_1(8613);
        set_picid_2(8613);

        set_level(60);
        set_value(44000);
        set_max_lasting(5499);
        set("cp", 110);
        set("pp", 65);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Lam Bảo Thạch Hạng Liên";
}
