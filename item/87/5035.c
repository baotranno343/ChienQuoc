
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 5; }

// 函数：构造处理
void create()
{
        set_name("Địch Khôn Yêu Đới");
        set_picid_1(8708);
        set_picid_2(8708);

        set_level(35);
        set_value(9750);
        set_max_lasting(5799);
        set("dp", 22);
        set("pp", 35);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Địch Khôn Yêu Đới";
}
