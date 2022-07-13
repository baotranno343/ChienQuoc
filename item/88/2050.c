
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Hạc Khiếu Lý");
        set_picid_1(8810);
        set_picid_2(8810);

        set_level(50);
        set_value(9100);
        set_max_lasting(8199);
        set("dp", 25);
        set("sp", 28);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Hạc Khiếu Lý";
}
