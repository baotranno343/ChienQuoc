
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Thần Linh Hạng Liên");
        set_picid_1(8662);
        set_picid_2(8662);

        set_level(110);
        set_value(69500);
        set_max_lasting(9399);
        set("cp", 0);
        set("pp", 115);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thần Linh Hạng Liên";
}
