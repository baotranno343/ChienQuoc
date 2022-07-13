
#include <equip.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Hiên Viên Kiếm");
        set_picid_1(7323);
        set_picid_2(7323);
        set_unit("Bính");

        set_level(130);
        set_value(57000);
        set_max_lasting(27599);
        set("ap", 256);
        set("!%", 30);
        set("spec.hp", 220);
        set("spec.hp*", 6);
        set("spec.mp*", 6);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return 23; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị “Kiếm Pháp”";
}
