
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Phi Hổ Yêu Đới");
        set_picid_1(8711);
        set_picid_2(8711);

        set_level(130);
        set_value(10000);
        set_max_lasting(16099);
        set("dp", 130);
        set("pp", 115);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Phi Hổ Yêu Đới";
}
