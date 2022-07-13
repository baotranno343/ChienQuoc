
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 9; }

// 函数：成品编号
int get_fin_type() { return 1007; }

// 函数：构造处理
void create()
{
        set_name("Hậu Nhẫn Kiếm");
        set_picid_1(7322);
        set_picid_2(7322);

        set_level(30);
        set_value(3000);
        set_max_lasting(4599);
        set("ap", 60);
        set("dp", 5);
        set("cp", 105);
        set("pp", 0);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_04; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Kiếm Pháp\"";
}
