
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Phượng Thiên Hài");
        set_picid_1(8812);
        set_picid_2(8812);

        set_level(120);
        set_value(30800);
        set_max_lasting(13399);
        set("dp", 56);
        set("sp", 70);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Phượng Thiên Hài";
}
