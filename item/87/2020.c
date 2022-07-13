
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Thanh Liễu Yêu Đới");
        set_picid_1(8711);
        set_picid_2(8711);

        set_level(20);
        set_value(2500);
        set_max_lasting(6699);
        set("dp", 23);
        set("pp", 8);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thanh Liễu Yêu Đới";
}
