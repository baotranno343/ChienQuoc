
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Cuồng Long Yêu Đới");
        set_picid_1(8714);
        set_picid_2(8714);

        set_level(70);
        set_value(15000);
        set_max_lasting(11199);
        set("dp", 73);
        set("pp", 58);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Cuồng Long Yêu Đới";
}
