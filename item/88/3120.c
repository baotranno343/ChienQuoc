
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Chiến Thần Hài");
        set_picid_1(8811);
        set_picid_2(8811);

        set_level(120);
        set_value(30800);
        set_max_lasting(13399);
        set("dp", 56);
		
        set("sp", 64);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Chiến Thần Hài";
}
