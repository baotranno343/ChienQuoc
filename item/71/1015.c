
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit MISSILE;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Mai Hoa Châm");
        set_picid_1(7101);
        set_picid_2(7101);

        set_level(15);
        set_value(1500);
        set_max_lasting(13099);
        set("ap", 39);
        set("dp", -8);
        set("cp", 0);
        set("sp", 0);

        setup();

        set_weapon_type(THROWING);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_00; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Ám Khí\"";
}
