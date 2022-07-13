
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Linh Thạch Hạng Liên");
        set_picid_1(8610);
        set_picid_2(8610);

        set_level(40);
        set_value(20500);
        set_max_lasting(7299);
        set("cp", 0);
        set("pp", 45);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Linh Thạch Hạng Liên";
}
