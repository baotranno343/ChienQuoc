
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 7; }

// 函数：构造处理
void create()
{
        set_name("Thải Vân Hạng Liên");
        set_picid_1(8609);
        set_picid_2(8609);

        set_level(30);
        set_value(17000);
        set_max_lasting(4999);
        set("cp", 50);
        set("pp", 40);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thải Vân Hạng Liên";
}
