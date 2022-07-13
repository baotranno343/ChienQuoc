
#include <equip.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("青冥剑");
        set_picid_1(7322);
        set_picid_2(7322);
        set_unit("柄");

        set_level(120);
        set_value(52000);
        set_max_lasting(26099);
        set("ap", 238);
        set("!%", 30);
        set("spec.hp", 200);
        set("spec.hp*", 6);
        set("spec.mp*", 6);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return 22; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị “Kiếm Pháp”";
}
