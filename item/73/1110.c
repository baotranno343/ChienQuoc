
#include <equip.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("倚天剑");
        set_picid_1(7321);
        set_picid_2(7321);
        set_unit("柄");

        set_level(110);
        set_value(47000);
        set_max_lasting(24599);
        set("ap", 220);
        set("!%", 28);
        set("spec.hp", 180);
        set("spec.hp*", 6);
        set("spec.mp*", 6);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return 21; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị “Kiếm Pháp”";
}
