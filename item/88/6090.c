
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 6; }

// 函数：构造处理
void create()
{
        set_name("Phi Long Lý");
        set_picid_1(8810);
        set_picid_2(8810);

        set_level(90);
        set_value(25000);
        set_max_lasting(7899);
        set("dp", 20);
        set("sp", 35);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Phi Long Lý";
}
