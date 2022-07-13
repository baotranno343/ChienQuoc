
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 3; }

// 函数：成品编号
int get_fin_type() { return 1009; }

// 函数：构造处理
void create()
{
        set_name("Trường Kích");
        set_picid_1(7409);
        set_picid_2(7409);

        set_level(30);
        set_value(3000);
        set_max_lasting(6099);
        set("ap", 99);
        set("dp", 0);
        set("cp", 0);
        set("pp", 0);

        setup();

        set_weapon_type(SPEAR);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_04; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Thương Pháp\"";
}
