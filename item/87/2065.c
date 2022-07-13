
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Tiêu Diêu Yêu Đới");
        set_picid_1(8712);
        set_picid_2(8712);

        set_level(65);
        set_value(13750);
        set_max_lasting(10699);
        set("dp", 68);
        set("pp", 53);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Tiêu Diêu Yêu Đới";
}
