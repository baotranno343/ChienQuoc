
#include <equip.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Huyền Thiết Kiếm");
        set_picid_1(7317);
        set_picid_2(7317);
        set_unit("柄");

        set_level(70);
        set_value(27000);
        set_max_lasting(18599);
        set("ap", 148);
        set("!%", 20);
        set("spec.hp", 100);
        set("spec.hp*", 4);
        set("spec.mp*", 4);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return 17; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị “Kiếm Pháp”";
}
