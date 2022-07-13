
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Kì Long Yêu Đới");
        set_picid_1(8714);
        set_picid_2(8714);

        set_level(90);
        set_value(20000);
        set_max_lasting(12999);
        set("dp", 93);
        set("pp", 78);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Kì Long Yêu Đới";
}
