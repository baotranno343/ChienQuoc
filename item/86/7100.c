
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 7; }

// 函数：构造处理
void create()
{
        set_name("Phượng Minh Hạng Liên");
        set_picid_1(8650);
        set_picid_2(8650);

        set_level(100);
        set_value(80000);
        set_max_lasting(6099);
        set("cp", 190);
        set("pp", 110);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Phượng Minh Hạng Liên";
}
