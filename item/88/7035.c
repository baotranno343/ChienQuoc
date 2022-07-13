
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 7; }

// 函数：构造处理
void create()
{
        set_name("Tâm Hoa Lý");
        set_picid_1(8807);
        set_picid_2(8807);

        set_level(35);
        set_value(5700);
        set_max_lasting(5399);
        set("dp", 9);
        set("sp", 13);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Tâm Hoa Lý";
}
