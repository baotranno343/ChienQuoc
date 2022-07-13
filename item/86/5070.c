
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 5; }

// 函数：构造处理
void create()
{
        set_name("Ngọc Phong Hạng Liên");
        set_picid_1(8652);
        set_picid_2(8652);

        set_level(70);
        set_value(53000);
        set_max_lasting(5599);
        set("cp", 128);
        set("pp", 76);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Ngọc Phong Hạng Liên";
}
