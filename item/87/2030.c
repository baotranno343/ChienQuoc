
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Bích Long Yêu Đới");
        set_picid_1(8711);
        set_picid_2(8711);

        set_level(30);
        set_value(5000);
        set_max_lasting(7599);
        set("dp", 33);
        set("pp", 18);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Bích Long Yêu Đới";
}
