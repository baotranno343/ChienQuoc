
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Thí Thần");
        set_picid_1(7319);
        set_picid_2(7319);

        set_level(120);
        set_value(52000);
        set_max_lasting(25599);
        set("ap", 250);
        set("dp", 33);
        set("cp", 310);
        set("sp", 26);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_14; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Kiếm Pháp\"";
}
