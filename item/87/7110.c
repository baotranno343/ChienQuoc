
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 7; }

// 函数：构造处理
void create()
{
        set_name("Viêm Lân Yêu Đới");
        set_picid_1(8714);
        set_picid_2(8714);

        set_level(110);
        set_value(36000);
        set_max_lasting(7999);
        set("dp", 98);
        set("pp", 112);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Viêm Lân Yêu Đới";
}
