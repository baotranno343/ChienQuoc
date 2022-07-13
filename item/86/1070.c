
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Phỉ Thuý Hạng Liên");
        set_picid_1(8604);
        set_picid_2(8604);

        set_level(70);
        set_value(41500);
        set_max_lasting(8199);
        set("cp", 0);
        set("pp", 70);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Phỉ Thuý Hạng Liên";
}
