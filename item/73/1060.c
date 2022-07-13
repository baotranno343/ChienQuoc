
#include <equip.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("玄冥剑");
        set_picid_1(7316);
        set_picid_2(7316);
        set_unit("柄");

        set_level(60);
        set_value(22000);
        set_max_lasting(17099);
        set("cp", 130);
        set("!%", 18);
        set("spec.hp", 80);
        set("spec.hp*", 2);
        set("spec.mp*", 2);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return 16; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị “Kiếm Pháp”";
}
