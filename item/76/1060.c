
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Long Xí Giản");
        set_picid_1(7313);
        set_picid_2(7313);

        set_level(60);
        set_value(22000);
        set_max_lasting(18599);
        set("ap", 131);
        set("dp", 15);
        set("cp", 160);
        set("sp", 14);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_07; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Kiếm Pháp\"";
}
