
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 5; }

// 函数：构造处理
void create()
{
        set_name("Thu Thuỷ Lý");
        set_picid_1(8805);
        set_picid_2(8805);

        set_level(45);
        set_value(9300);
        set_max_lasting(5899);
        set("dp", 11);
        set("sp", 17);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thu Thuỷ Lý";
}
