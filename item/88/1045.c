
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Truy Phong Lý");
        set_picid_1(8803);
        set_picid_2(8803);

        set_level(45);
        set_value(7600);
        set_max_lasting(7799);
        set("dp", 22);
        set("sp", 21);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Truy Phong Lý";
}
