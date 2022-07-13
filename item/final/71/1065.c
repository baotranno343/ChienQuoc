
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit MISSILE;

// 函数：适用门派
int get_family() { return 4; }

// 函数：成品编号
int get_fin_type() { return 1123; }

// 函数：构造处理
void create()
{
        set_name("Thiên Lang Thứ");
        set_picid_1(7116);
        set_picid_2(7116);

        set_level(65);
        set_value(6500);
        set_max_lasting(8099);
        set("ap", 171);
        set("dp", 11);
        set("cp", 0);
        set("pp", 0);

        setup();

        set_weapon_type(THROWING);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_07; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Ám Khí\"";
}
