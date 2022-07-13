
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 2; }

// 函数：成品编号
int get_fin_type() { return 1126; }

// 函数：构造处理
void create()
{
        set_name("Trảm Long Đao");
        set_picid_1(7220);
        set_picid_2(7220);

        set_level(75);
        set_value(7500);
        set_max_lasting(13099);
        set("ap", 180);
        set("dp", 0);
        set("cp", 0);
        set("pp", 0);

        setup();

        set_weapon_type(BLADE);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_08; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Đao Pháp\"";
}
