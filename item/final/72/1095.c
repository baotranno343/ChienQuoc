
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 2; }

// 函数：成品编号
int get_fin_type() { return 1138; }

// 函数：构造处理
void create()
{
        set_name("Phá Phong Đao");
        set_picid_1(7205);
        set_picid_2(7205);

        set_level(95);
        set_value(9500);
        set_max_lasting(14099);
        set("ap", 220);
        set("dp", 0);
        set("cp", 0);
        set("pp", 0);

        setup();

        set_weapon_type(BLADE);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_10; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Đao Pháp\"";
}
