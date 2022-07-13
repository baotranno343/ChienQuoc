
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 7; }

// 函数：构造处理
void create()
{
        set_name("Hắc Long Hạng Liên");
        set_picid_1(8656);
        set_picid_2(8656);

        set_level(40);
        set_value(26000);
        set_max_lasting(5199);
        set("cp", 70);
        set("pp", 50);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Hắc Long Hạng Liên";
}
