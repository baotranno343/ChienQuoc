
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Tinh Quang Hạng Liên");
        set_picid_1(8600);
        set_picid_2(8600);

        set_level(30);
        set_value(15000);
        set_max_lasting(5799);
        set("cp", 0);
        set("pp", 32);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Tinh Quang Hạng Liên";
}
