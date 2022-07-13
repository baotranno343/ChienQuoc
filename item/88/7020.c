
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 7; }

// 函数：构造处理
void create()
{
        set_name("Cổ Giáp Hài");
        set_picid_1(8806);
        set_picid_2(8806);

        set_level(20);
        set_value(1200);
        set_max_lasting(4799);
        set("dp", 6);
        set("sp", 7);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Cổ Giáp Hài";
}
