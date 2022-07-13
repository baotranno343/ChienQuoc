
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 9; }

// 函数：成品编号
int get_fin_type() { return 1143; }

// 函数：构造处理
void create()
{
        set_name("Xích Tiêu");
        set_picid_1(7314);
        set_picid_2(7314);

        set_level(105);
        set_value(10500);
        set_max_lasting(14599);
        set("ap", 210);
        set("dp", 20);
        set("cp", 330);
        set("pp", 0);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_11; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Kiếm Pháp\"";
}
