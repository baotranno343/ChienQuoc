
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 7; }

// 函数：构造处理
void create()
{
        set_name("Hồn Sương Yêu Đới");
        set_picid_1(8705);
        set_picid_2(8705);

        set_level(40);
        set_value(11500);
        set_max_lasting(5899);
        set("dp", 28);
        set("pp", 42);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Hồn Sương Yêu Đới";
}
