
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Long Ngâm Hạng Liên");
        set_picid_1(8662);
        set_picid_2(8662);

        set_level(120);
        set_value(76500);
        set_max_lasting(9699);
        set("cp", 0);
        set("pp", 120);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Long Ngâm Hạng Liên";
}
