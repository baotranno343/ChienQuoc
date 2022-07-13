
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 6; }

// 函数：构造处理
void create()
{
        set_name("Phi Thiên Vũ Đới");
        set_picid_1(8713);
        set_picid_2(8713);

        set_level(100);
        set_value(39500);
        set_max_lasting(16099);
        set("dp", 115);
        set("pp", 130);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Phi Thiên Vũ Đới";
}
