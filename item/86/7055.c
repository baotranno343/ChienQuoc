
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 7; }

// 函数：构造处理
void create()
{
        set_name("Thuỷ Văn Hạng Liên");
        set_picid_1(8653);
        set_picid_2(8653);

        set_level(55);
        set_value(39500);
        set_max_lasting(5399);
        set("cp", 100);
        set("pp", 65);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thuỷ Văn Hạng Liên";
}
