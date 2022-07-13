
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 7; }

// 函数：构造处理
void create()
{
        set_name("Thiết Yêu Đới");
        set_picid_1(8703);
        set_picid_2(8703);

        set_level(15);
        set_value(2750);
        set_max_lasting(5199);
        set("dp", 3);
        set("pp", 17);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thiết Yêu Đới";
}
