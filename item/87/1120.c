
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Tinh Thần Yêu Đới");
        set_picid_1(8713);
        set_picid_2(8713);

        set_level(120);
        set_value(27500);
        set_max_lasting(15699);
        set("dp", 120);
        set("pp", 105);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Tinh Thần Yêu Đới";
}
