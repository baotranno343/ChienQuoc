
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Cuồng Long Lý");
        set_picid_1(8810);
        set_picid_2(8810);

        set_level(70);
        set_value(15300);
        set_max_lasting(9699);
        set("dp", 34);
        set("sp", 40);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Cuồng Long Lý";
}
