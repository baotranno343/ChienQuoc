
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 7; }

// 函数：构造处理
void create()
{
        set_name("Triệt Vân Yêu Đới");
        set_picid_1(8710);
        set_picid_2(8710);

        set_level(60);
        set_value(18500);
        set_max_lasting(6499);
        set("dp", 48);
        set("pp", 62);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Triệt Vân Yêu Đới";
}
