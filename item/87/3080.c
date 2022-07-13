
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Vân Long Yêu Đới");
        set_picid_1(8710);
        set_picid_2(8710);

        set_level(80);
        set_value(17500);
        set_max_lasting(12099);
        set("dp", 78);
        set("pp", 65);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Vân Long Yêu Đới";
}
