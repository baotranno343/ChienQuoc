
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Phi Hổ Lý");
        set_picid_1(8810);
        set_picid_2(8810);

        set_level(45);
        set_value(7600);
        set_max_lasting(7799);
        set("dp", 22);
        set("sp", 25);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Phi Hổ Lý";
}
