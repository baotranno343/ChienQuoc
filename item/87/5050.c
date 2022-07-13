
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 5; }

// 函数：构造处理
void create()
{
        set_name("Dực Phi Yêu Đới");
        set_picid_1(8712);
        set_picid_2(8712);

        set_level(50);
        set_value(15000);
        set_max_lasting(6199);
        set("dp", 37);
        set("pp", 50);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Dực Phi Yêu Đới";
}
