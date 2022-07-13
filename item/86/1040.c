
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Tượng Nha Hạng Liên");
        set_picid_1(8601);
        set_picid_2(8601);

        set_level(40);
        set_value(20500);
        set_max_lasting(7299);
        set("cp", 0);
        set("pp", 40);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Tượng Nha Hạng Liên";
}
