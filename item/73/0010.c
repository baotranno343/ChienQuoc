
#include <equip.h>

inherit WEAPON;

// 函数：构造处理
void create()
{
        set_name("Thanh Phong Kiếm");
        set_picid_1(7301);
        set_picid_2(7301);
        set_unit("柄");

        set_level(10);
        set_value(900);
        set_max_lasting(6099);
        set("ap", 22);
        set("!%", 8);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return 1; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị “Kiếm Pháp”";
}
