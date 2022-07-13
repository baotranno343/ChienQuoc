
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 3; }

// 函数：成品编号
int get_fin_type() { return 1040; }

// 函数：构造处理
void create()
{
        set_name("Hoa Điêu Côn");
        set_picid_1(7521);
        set_picid_2(7521);

        set_level(80);
        set_value(8000);
        set_max_lasting(14099);
        set("ap", 196);
        set("dp", 30);
        set("cp", 0);
        set("pp", 0);

        setup();

        set_weapon_type(STICK);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_09; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Bổng Pháp\"";
}
