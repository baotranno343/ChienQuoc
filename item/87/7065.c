
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 7; }

// 函数：构造处理
void create()
{
        set_name("Kì Mộc Yêu Đới");
        set_picid_1(8712);
        set_picid_2(8712);

        set_level(65);
        set_value(20250);
        set_max_lasting(6699);
        set("dp", 53);
        set("pp", 67);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Kì Mộc Yêu Đới";
}
