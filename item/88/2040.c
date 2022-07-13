
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Vũ Thiên Lý");
        set_picid_1(8808);
        set_picid_2(8808);

        set_level(40);
        set_value(6000);
        set_max_lasting(7399);
        set("dp", 20);
        set("sp", 22);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Vũ Thiên Lý";
}
