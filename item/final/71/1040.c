
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit MISSILE;

// 函数：适用门派
int get_family() { return 4; }

// 函数：成品编号
int get_fin_type() { return 1013; }

// 函数：构造处理
void create()
{
        set_name("Phá Giáp Châm");
        set_picid_1(7101);
        set_picid_2(7101);

        set_level(40);
        set_value(4000);
        set_max_lasting(6599);
        set("ap", 93);
        set("dp", 4);
        set("cp", 0);
        set("pp", 0);

        setup();

        set_weapon_type(THROWING);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_05; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Ám Khí\"";
}
