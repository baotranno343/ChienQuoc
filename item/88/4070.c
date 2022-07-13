
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Thiên Uy Hài");
        set_picid_1(8808);
        set_picid_2(8808);

        set_level(70);
        set_value(13500);
        set_max_lasting(9699);
        set("dp", 16);
        set("sp", 70);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thiên Uy Hài";
}
