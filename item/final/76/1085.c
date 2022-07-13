
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 9; }

// 函数：成品编号
int get_fin_type() { return 1131; }

// 函数：构造处理
void create()
{
        set_name("Thuỷ Nguyệt Kiếm");
        set_picid_1(7303);
        set_picid_2(7303);

        set_level(85);
        set_value(8500);
        set_max_lasting(13599);
        set("ap", 170);
        set("dp", 10);
        set("cp", 270);
        set("pp", 0);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_09; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Kiếm Pháp\"";
}
