
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 7; }

// 函数：构造处理
void create()
{
        set_name("Kì Mộc Lý");
        set_picid_1(8808);
        set_picid_2(8808);

        set_level(65);
        set_value(16300);
        set_max_lasting(6799);
        set("dp", 15);
        set("sp", 25);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Kì Mộc Lý";
}
