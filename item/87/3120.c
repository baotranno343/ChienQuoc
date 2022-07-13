
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Chiến Thần Yêu Đới");
        set_picid_1(8714);
        set_picid_2(8714);

        set_level(120);
        set_value(27500);
        set_max_lasting(15699);
        set("dp", 118);
        set("pp", 105);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Chiến Thần Yêu Đới";
}
