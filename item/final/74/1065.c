
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 3; }

// 函数：成品编号
int get_fin_type() { return 1121; }

// 函数：构造处理
void create()
{
        set_name("Bồng Lai Mâu");
        set_picid_1(7415);
        set_picid_2(7415);

        set_level(65);
        set_value(6500);
        set_max_lasting(8099);
        set("ap", 146);
        set("dp", 11);
        set("cp", 0);
        set("pp", 0);

        setup();

        set_weapon_type(SPEAR);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_07; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Thương Pháp\"";
}
