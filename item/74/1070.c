
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Xích Viêm Thương");
        set_picid_1(7410);
        set_picid_2(7410);

        set_level(70);
        set_value(27000);
        set_max_lasting(18599);
        set("ap", 167);
        set("dp", 0);
        set("cp", 0);
        set("sp", -30);

        setup();

        set_weapon_type(SPEAR);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_09; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Thương Pháp\"";
}
