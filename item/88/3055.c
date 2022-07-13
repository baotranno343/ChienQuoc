
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Phi Báo Lý");
        set_picid_1(8810);
        set_picid_2(8810);

        set_level(55);
        set_value(10600);
        set_max_lasting(8599);
        set("dp", 27);
        set("sp", 25);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Phi Báo Lý";
}
