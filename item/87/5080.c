
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 5; }

// 函数：构造处理
void create()
{
        set_name("Trảm Hầu Yêu Đới");
        set_picid_1(8710);
        set_picid_2(8710);

        set_level(80);
        set_value(25500);
        set_max_lasting(7099);
        set("dp", 67);
        set("pp", 80);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Trảm Hầu Yêu Đới";
}
