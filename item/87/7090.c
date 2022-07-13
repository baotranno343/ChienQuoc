
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 7; }

// 函数：构造处理
void create()
{
        set_name("Minh Quang Yêu Đới");
        set_picid_1(8710);
        set_picid_2(8710);

        set_level(90);
        set_value(29000);
        set_max_lasting(7399);
        set("dp", 78);
        set("pp", 92);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Minh Quang Yêu Đới";
}
