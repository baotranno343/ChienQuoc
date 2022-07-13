
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Bá Vương Lý");
        set_picid_1(8812);
        set_picid_2(8812);

        set_level(100);
        set_value(24600);
        set_max_lasting(11899);
        set("dp", 47);
		
        set("sp", 52);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Bá Vương Lý";
}
