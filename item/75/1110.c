
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Chấn Thiên");
        set_picid_1(7522);
        set_picid_2(7522);

        set_level(110);
        set_value(47000);
        set_max_lasting(25099);
        set("ap", 258);
        set("dp", -46);
        set("cp", 0);
        set("sp", 0);

        setup();

        set_weapon_type(STICK);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_13; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Bổng Pháp\"";
}
