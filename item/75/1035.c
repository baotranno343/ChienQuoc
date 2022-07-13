
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Tử Kim Côn");
        set_picid_1(7515);
        set_picid_2(7515);

        set_level(35);
        set_value(8500);
        set_max_lasting(14599);
        set("ap", 98);
        set("dp", -16);
        set("cp", 0);
        set("sp", 0);

        setup();

        set_weapon_type(STICK);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_04; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Bổng Pháp\"";
}
