
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 6; }

// 函数：构造处理
void create()
{
        set_name("Thanh Long Yêu Đới");
        set_picid_1(8711);
        set_picid_2(8711);

        set_level(30);
        set_value(8000);
        set_max_lasting(5599);
        set("dp", 15);
        set("pp", 30);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thanh Long Yêu Đới";
}
