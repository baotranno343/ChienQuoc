
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 5; }

// 函数：构造处理
void create()
{
        set_name("Thuỷ Hồn Hạng Liên");
        set_picid_1(8657);
        set_picid_2(8657);

        set_level(65);
        set_value(48500);
        set_max_lasting(5499);
        set("cp", 118);
        set("pp", 71);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thuỷ Hồn Hạng Liên";
}
