
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 7; }

// 函数：构造处理
void create()
{
        set_name("Thất Hà Hạng Liên");
        set_picid_1(8650);
        set_picid_2(8650);

        set_level(80);
        set_value(62000);
        set_max_lasting(5799);
        set("cp", 150);
        set("pp", 90);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thất Hà Hạng Liên";
}
