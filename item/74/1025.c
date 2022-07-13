
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Hàn Cương Kích");
        set_picid_1(7409);
        set_picid_2(7409);

        set_level(25);
        set_value(4500);
        set_max_lasting(8599);
        set("ap", 75);
        set("dp", 0);
        set("cp", 0);
        set("sp", -12);

        setup();

        set_weapon_type(SPEAR);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_03; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Thương Pháp\"";
}
