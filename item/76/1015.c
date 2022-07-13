
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Trường Phong Kiếm");
        set_picid_1(7322);
        set_picid_2(7322);

        set_level(15);
        set_value(1200);
        set_max_lasting(10099);
        set("ap", 42);
        set("dp", 6);
        set("cp", 25);
        set("sp", 5);

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
