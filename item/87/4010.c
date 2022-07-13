
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Bố Yêu Đới");
        set_picid_1(8703);
        set_picid_2(8703);

        set_level(10);
        set_value(1100);
        set_max_lasting(5799);
        set("dp", 2);
        set("pp", 2);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Bố Yêu Đới";
}
