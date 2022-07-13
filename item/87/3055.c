
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Phi Báo Yêu Đới");
        set_picid_1(8710);
        set_picid_2(8710);

        set_level(55);
        set_value(11250);
        set_max_lasting(9799);
        set("dp", 53);
        set("pp", 40);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Phi Báo Yêu Đới";
}
