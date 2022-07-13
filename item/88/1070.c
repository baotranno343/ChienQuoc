
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Thần Phong Lý");
        set_picid_1(8805);
        set_picid_2(8805);

        set_level(70);
        set_value(15300);
        set_max_lasting(9699);
        set("dp", 34);
        set("sp", 36);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thần Phong Lý";
}
