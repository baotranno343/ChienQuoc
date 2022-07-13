
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Tàn Dương Yêu Đới");
        set_picid_1(8707);
        set_picid_2(8707);

        set_level(110);
        set_value(25000);
        set_max_lasting(14799);
        set("dp", 110);
        set("pp", 95);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Tàn Dương Yêu Đới";
}
