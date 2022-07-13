
#include <equip.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Thái cực kiếm");
        set_picid_1(7314);
        set_picid_2(7314);
        set_unit("柄");

        set_level(40);
        set_value(12000);
        set_max_lasting(14599);
        set("ap", 94);
        set("!%", 14);
        set("spec.hp", 40);
        set("spec.hp*", 2);
        set("spec.mp*", 2);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return 14; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị “Kiếm Pháp”";
}
