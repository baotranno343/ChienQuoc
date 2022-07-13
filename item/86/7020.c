
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 7; }

// 函数：构造处理
void create()
{
        set_name("Thiết Hạng Liên");
        set_picid_1(8612);
        set_picid_2(8612);

        set_level(20);
        set_value(8000);
        set_max_lasting(4899);
        set("cp", 30);
        set("pp", 30);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thiết Hạng Liên";
}
