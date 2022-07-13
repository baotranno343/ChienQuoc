
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 5; }

// 函数：构造处理
void create()
{
        set_name("Cổ Đằng Yêu Đới");
        set_picid_1(8706);
        set_picid_2(8706);

        set_level(20);
        set_value(4500);
        set_max_lasting(5299);
        set("dp", 7);
        set("pp", 20);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Cổ Đằng Yêu Đới";
}
