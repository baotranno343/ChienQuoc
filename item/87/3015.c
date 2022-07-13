
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Thiết Yêu Đới");
        set_picid_1(8703);
        set_picid_2(8703);

        set_level(15);
        set_value(1250);
        set_max_lasting(6199);
        set("dp", 13);
        set("pp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thiết Yêu Đới";
}
