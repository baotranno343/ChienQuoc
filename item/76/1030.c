
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Kim Xà Kiếm");
        set_picid_1(7320);
        set_picid_2(7320);

        set_level(30);
        set_value(7000);
        set_max_lasting(13599);
        set("ap", 72);
        set("dp", 9);
        set("cp", 70);
        set("sp", 8);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_04; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Kiếm Pháp\"";
}
