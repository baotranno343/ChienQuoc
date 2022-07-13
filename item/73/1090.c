
#include <equip.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("莫邪");
        set_picid_1(7319);
        set_picid_2(7319);
        set_unit("柄");

        set_level(90);
        set_value(37000);
        set_max_lasting(21599);
        set("ap", 184);
        set("!%", 24);
        set("spec.hp", 140);
        set("spec.hp*", 4);
        set("spec.mp*", 4);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return 19; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị “Kiếm Pháp”";
}
