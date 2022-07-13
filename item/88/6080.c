
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 6; }

// 函数：构造处理
void create()
{
        set_name("Huỳnh Quang Lý");
        set_picid_1(8810);
        set_picid_2(8810);

        set_level(80);
        set_value(21500);
        set_max_lasting(7399);
        set("dp", 18);
        set("sp", 31);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Huỳnh Quang Lý";
}
