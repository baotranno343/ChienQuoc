
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Thanh Liễu Hài");
        set_picid_1(8803);
        set_picid_2(8803);

        set_level(20);
        set_value(2000);
        set_max_lasting(5899);
        set("dp", 11);
        set("sp", 10);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thanh Liễu Hài";
}
