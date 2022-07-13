
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Hư Minh Hạng Liên");
        set_picid_1(8664);
        set_picid_2(8664);

        set_level(120);
        set_value(84750);
        set_max_lasting(8499);
        set("cp", 0);
        set("pp", 122);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Hư Minh Hạng Liên";
}
