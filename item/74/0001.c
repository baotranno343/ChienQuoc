
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 8; }

// 函数：构造处理
void create()
{
        set_name("Trúc Mâu");
        set_picid_1(7400);
        set_picid_2(7400);

        set_level(0);
        set_value(100);
        set_max_lasting(3899);
        set("ap", 11);
        set("dp", 0);
        set("cp", 0);
        set("sp", -3);

        setup();

        set_weapon_type(SPEAR);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_01; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Thương Pháp\"";
}
