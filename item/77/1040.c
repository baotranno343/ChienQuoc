
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 5; }

// 函数：构造处理
void create()
{
        set_name("Xích Dương Kiếm");
        set_picid_1(7621);
        set_picid_2(7621);

        set_level(40);
        set_value(18000);
        set_max_lasting(6099);
        set("ap", 80);
        set("dp", 0);
        set("cp", 130);
        set("sp", 0);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_05; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Kiếm Pháp\"";
}
