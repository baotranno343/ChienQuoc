
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 8; }

// 函数：构造处理
void create()
{
        set_name("Cương Mâu");
        set_picid_1(7403);
        set_picid_2(7403);

        set_level(15);
        set_value(1200);
        set_max_lasting(6599);
        set("ap", 54);
        set("dp", 0);
        set("cp", 0);
        set("sp", -8);

        setup();

        set_weapon_type(SPEAR);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_02; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Thương Pháp\"";
}
