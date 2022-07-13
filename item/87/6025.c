
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 6; }

// 函数：构造处理
void create()
{
        set_name("Lam Đoạn Yêu Đới");
        set_picid_1(8711);
        set_picid_2(8711);

        set_level(25);
        set_value(6250);
        set_max_lasting(5499);
        set("dp", 10);
        set("pp", 25);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Lam Đoạn Yêu Đới";
}
