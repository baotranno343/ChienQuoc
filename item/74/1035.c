
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Thích Thanh Thương");
        set_picid_1(7402);
        set_picid_2(7402);

        set_level(35);
        set_value(8500);
        set_max_lasting(14099);
        set("ap", 95);
        set("dp", 0);
        set("cp", 0);
        set("sp", -16);

        setup();

        set_weapon_type(SPEAR);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_04; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Thương Pháp\"";
}
