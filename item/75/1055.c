
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Hạo Xí Côn");
        set_picid_1(7513);
        set_picid_2(7513);

        set_level(55);
        set_value(19000);
        set_max_lasting(18099);
        set("ap", 141);
        set("dp", -24);
        set("cp", 0);
        set("sp", 0);

        setup();

        set_weapon_type(STICK);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_06; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Bổng Pháp\"";
}
