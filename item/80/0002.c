#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 8; }

// 函数：构造处理
void create()
{
        set_name("射手皮带");
        set_picid_1(8705);
        set_picid_2(8705);

	set_unit("条");
        set_level(12);
        set_value(1500);
        set_max_lasting(3699);
        set("dp", 13);
	set("!%", 10);
        setup();

}

// 函数：获取描述
string get_desc()
{
        return "射手皮带";
}
