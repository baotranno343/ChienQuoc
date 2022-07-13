
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Phá Địch Hài");
        set_picid_1(8810);
        set_picid_2(8810);

        set_level(40);
        set_value(6000);
        set_max_lasting(7399);
        set("dp", 20);
        set("sp", 16);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Phá Địch Hài";
}
