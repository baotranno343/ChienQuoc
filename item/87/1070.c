
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Thần Phong Yêu Đới");
        set_picid_1(8710);
        set_picid_2(8710);

        set_level(70);
        set_value(15000);
        set_max_lasting(11199);
        set("dp", 70);
        set("pp", 55);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thần Phong Yêu Đới";
}
