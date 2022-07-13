
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Kỳ Long Lý");
        set_picid_1(8810);
        set_picid_2(8810);

        set_level(90);
        set_value(21500);
        set_max_lasting(11199);
        set("dp", 43);
        set("sp", 52);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Kỳ Long Lý";
}
