
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 5; }

// 函数：构造处理
void create()
{
        set_name("Khâm Thiên Lý");
        set_picid_1(8812);
        set_picid_2(8812);

        set_level(120);
        set_value(35500);
        set_max_lasting(9199);
        set("dp", 26);
        set("sp", 47);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Khâm Thiên Lý";
}
