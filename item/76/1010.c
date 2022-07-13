
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Truy Phong Kiếm");
        set_picid_1(7322);
        set_picid_2(7322);

        set_level(10);
        set_value(900);
        set_max_lasting(9099);
        set("ap", 32);
        set("dp", 5);
        set("cp", 10);
        set("sp", 4);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_02; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Kiếm Pháp\"";
}
