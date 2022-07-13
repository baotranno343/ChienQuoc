
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 8; }

// 函数：构造处理
void create()
{
        set_name("Trường Mộc Côn");
        set_picid_1(7500);
        set_picid_2(7500);

        set_level(0);
        set_value(450);
        set_max_lasting(4599);
        set("ap", 28);
        set("dp", -4);
        set("cp", 0);
        set("sp", 0);

        setup();

        set_weapon_type(STICK);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_01; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Bổng Pháp\"";
}
