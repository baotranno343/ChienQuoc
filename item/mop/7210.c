
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 8; }

// 函数：构造处理
void create()
{
        set_name("勇敢者之刃");
        set_picid_1(7225);
        set_picid_2(7225);

        set_level(0);
        set_value(1);
        set_max_lasting(1099);
        set("ap", 30);
        set("dp", 0);
        set("cp", 0);
        set("sp", 0);
	set_no_give(1);
        setup();

        set_weapon_type(BLADE);
}

// 函数：获取描述
string get_desc()
{
        return "供勇敢者使用，无等级限制、无门派限制。";
}
