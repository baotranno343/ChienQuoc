
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Thanh Phong Kiếm");
        set_picid_1(7318);
        set_picid_2(7318);

        set_level(20);
        set_value(3000);
        set_max_lasting(12599);
        set("ap", 52);
        set("dp", 7);
        set("cp", 40);
        set("sp", 6);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_03; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Kiếm Pháp\"";
}
