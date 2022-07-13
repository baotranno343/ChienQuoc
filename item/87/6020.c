
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 6; }

// 函数：构造处理
void create()
{
        set_name("Tế Ma Yêu Đới");
        set_picid_1(8709);
        set_picid_2(8709);

        set_level(20);
        set_value(4500);
        set_max_lasting(5299);
        set("dp", 5);
        set("pp", 20);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Tế Ma Yêu Đới";
}
