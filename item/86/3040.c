
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Thái Thạch Hạng Liên");
        set_picid_1(8609);
        set_picid_2(8609);

        set_level(40);
        set_value(20500);
        set_max_lasting(7299);
        set("cp", 0);
        set("pp", 35);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thái Thạch Hạng Liên";
}
