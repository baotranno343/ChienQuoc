
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Hổ Phách Hạng Liên");
        set_picid_1(8603);
        set_picid_2(8603);

        set_level(60);
        set_value(34500);
        set_max_lasting(7899);
        set("cp", 0);
        set("pp", 60);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Hổ Phách Hạng Liên";
}
