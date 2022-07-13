
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 7; }

// 函数：构造处理
void create()
{
        set_name("Hắc Thiết Hạng Liên");
        set_picid_1(8607);
        set_picid_2(8607);

        set_level(25);
        set_value(12500);
        set_max_lasting(4899);
        set("cp", 40);
        set("pp", 35);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Hắc Thiết Hạng Liên";
}
