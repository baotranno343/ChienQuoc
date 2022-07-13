
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 9; }

// 函数：成品编号
int get_fin_type() { return 1155; }

// 函数：构造处理
void create()
{
        set_name("Khai Dương Kiếm");
        set_picid_1(7323);
        set_picid_2(7323);

        set_level(120);
        set_value(12000);
        set_max_lasting(16099);
        set("ap", 250);
        set("dp", 50);
        set("cp", 385);
        set("pp", 0);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_13; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Kiếm Pháp\"";
}
