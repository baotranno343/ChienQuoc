
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Thái Cực Kiếm");
        set_picid_1(7617);
        set_picid_2(7617);

        set_level(70);
        set_value(27000);
        set_max_lasting(20599);
        set("ap", 150);
        set("dp", 17);
        set("cp", 190);
        set("sp", 16);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_09; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Kiếm Pháp\"";
}
