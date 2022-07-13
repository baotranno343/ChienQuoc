
#include <equip.h>

inherit WEAPON;

// 函数：构造处理
void create()
{
        set_name("木剑");
        set_picid_1(7200);
        set_picid_2(7200);
        set_unit("柄");

        set_level(0);
        set_value(1);
        set_max_lasting(900);
        set("ap", 8);
        set("!%", 7);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取描述
string get_desc()
{
        return "“剑法”装备";
}
