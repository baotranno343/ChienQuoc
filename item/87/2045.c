
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Phi Hổ Yêu Đới");
        set_picid_1(8705);
        set_picid_2(8705);

        set_level(45);
        set_value(8750);
        set_max_lasting(8899);
        set("dp", 48);
        set("pp", 33);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Phi Hổ Yêu Đới";
}
