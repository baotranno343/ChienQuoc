
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Linh Lung Yêu Đới");
        set_picid_1(8705);
        set_picid_2(8705);

        set_level(35);
        set_value(6250);
        set_max_lasting(7999);
        set("dp", 38);
        set("pp", 23);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Linh Lung Yêu Đới";
}
