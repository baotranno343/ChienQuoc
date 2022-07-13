
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Long Bì Yêu Đới");
        set_picid_1(8705);
        set_picid_2(8705);

        set_level(65);
        set_value(13750);
        set_max_lasting(8599);
        set("dp", 55);
        set("pp", 55);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Long Bì Yêu Đới";
}
