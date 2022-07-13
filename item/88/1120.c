
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Tinh Thần Lý");
        set_picid_1(8808);
        set_picid_2(8808);

        set_level(120);
        set_value(30800);
        set_max_lasting(13399);
        set("dp", 56);
        set("sp", 66);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Tinh Thần Lý";
}
