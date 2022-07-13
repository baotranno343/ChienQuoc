
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Đồng Hạng Liên");
        set_picid_1(8608);
        set_picid_2(8608);

        set_level(10);
        set_value(1800);
        set_max_lasting(5199);
        set("cp", 0);
        set("pp", 12);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Đồng Hạng Liên";
}
