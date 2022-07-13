
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Thanh Hồng Kiếm");
        set_picid_1(7315);
        set_picid_2(7315);

        set_level(65);
        set_value(24000);
        set_max_lasting(19599);
        set("ap", 141);
        set("dp", 16);
        set("cp", 175);
        set("sp", 15);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_08; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Kiếm Pháp\"";
}
