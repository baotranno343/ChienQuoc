
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Truy Vân Yêu Đới");
        set_picid_1(8710);
        set_picid_2(8710);

        set_level(45);
        set_value(9150);
        set_max_lasting(7399);
        set("dp", 35);
        set("pp", 35);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Truy Vân Yêu Đới";
}
