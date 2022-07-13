
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 6; }

// 函数：构造处理
void create()
{
        set_name("Can Vân Lý");
        set_picid_1(8810);
        set_picid_2(8810);

        set_level(110);
        set_value(32000);
        set_max_lasting(8799);
        set("dp", 24);
        set("sp", 43);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Can Vân Lý";
}
