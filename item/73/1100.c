
#include <equip.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("金蛇剑");
        set_picid_1(7320);
        set_picid_2(7320);
        set_unit("柄");

        set_level(100);
        set_value(42000);
        set_max_lasting(23099);
        set("ap", 202);
        set("!%", 26);
        set("spec.hp", 160);
        set("spec.hp*", 4);
        set("spec.mp*", 4);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return 20; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị “Kiếm Pháp”";
}
