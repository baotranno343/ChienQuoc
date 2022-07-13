#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 8; }

// 函数：构造处理
void create()
{
        set_name("热血头巾");
        set_picid_1(8511);
        set_picid_2(8511);

        set_level(5);
        set_value(1500);
        set_max_lasting(3699);
        set("dp", 3);
	set("hp", 10);
        setup();

        set_head_code(50);
}

// 函数：获取描述
string get_desc()
{
        return "鹰目头巾";
}
