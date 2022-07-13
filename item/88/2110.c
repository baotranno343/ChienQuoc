
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Tử Vân Lý");
        set_picid_1(8812);
        set_picid_2(8812);

        set_level(110);
        set_value(27700);
        set_max_lasting(12699);
        set("dp", 52);
        set("sp", 64);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Tử Vân Lý";
}
