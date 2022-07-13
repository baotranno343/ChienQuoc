
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Hàn Thanh Kiếm");
        set_picid_1(7318);
        set_picid_2(7318);

        set_level(25);
        set_value(4500);
        set_max_lasting(13099);
        set("ap", 62);
        set("dp", 8);
        set("cp", 55);
        set("sp", 7);

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
