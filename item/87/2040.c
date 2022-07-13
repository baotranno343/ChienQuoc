
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Vũ Thiên Yêu Đới");
        set_picid_1(8712);
        set_picid_2(8712);

        set_level(40);
        set_value(7500);
        set_max_lasting(8499);
        set("dp", 43);
        set("pp", 28);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Vũ Thiên Yêu Đới";
}
