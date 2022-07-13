
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 7; }

// 函数：构造处理
void create()
{
        set_name("Minh Vực Hạng Liên");
        set_picid_1(8656);
        set_picid_2(8656);

        set_level(60);
        set_value(44000);
        set_max_lasting(5499);
        set("cp", 110);
        set("pp", 70);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Minh Vực Hạng Liên";
}
