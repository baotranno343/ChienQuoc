
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Vân Long Chiến Hài");
        set_picid_1(8812);
        set_picid_2(8812);

        set_level(80);
        set_value(18400);
        set_max_lasting(10399);
        set("dp", 38);
		
        set("sp", 40);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Vân Long Chiến Hài";
}
