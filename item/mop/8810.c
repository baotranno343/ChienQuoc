
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 8; }

// 函数：构造处理
void create()
{
        set_name("勇敢者长靴");
        set_picid_1(8800);
        set_picid_2(8800);

        set_level(0);
        set_value(1);
        set_max_lasting(10099);
        set("dp", 5);
        set("sp", 5);
	set_no_give(1);
        setup();
}

// 函数：获取描述
string get_desc()
{
        return "供勇敢者使用，无等级限制、无门派限制。";
}
