
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Hiên Duyên Lý");
        set_picid_1(8810);
        set_picid_2(8810);

        set_level(110);
        set_value(23500);
        set_max_lasting(13299);
        set("dp", 24);
        set("sp", 118);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Hiên Duyên Lý";
}
