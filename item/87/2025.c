
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Phất Hiểu Yêu Đới");
        set_picid_1(8707);
        set_picid_2(8707);

        set_level(25);
        set_value(3750);
        set_max_lasting(7099);
        set("dp", 28);
        set("pp", 13);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Phất Hiểu Yêu Đới";
}
