
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 6; }

// 函数：构造处理
void create()
{
        set_name("Huyền Minh Giản");
        set_picid_1(7620);
        set_picid_2(7620);

        set_level(80);
        set_value(42000);
        set_max_lasting(8099);
        set("ap", 160);
        set("dp", 0);
        set("cp", 255);
        set("sp", 0);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_10; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Kiếm Pháp\"";
}
