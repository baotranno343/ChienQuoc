
#include <equip.h>

inherit WEAPON;

// 函数：构造处理
void create()
{
        set_name("Cự quyết kiếm");
        set_picid_1(7304);
        set_picid_2(7304);
        set_unit("柄");

        set_level(40);
        set_value(6000);
        set_max_lasting(12599);
        set("ap", 64);
        set("!%", 11);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return 4; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị “Kiếm Pháp”";
}
