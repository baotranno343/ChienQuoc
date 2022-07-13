
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Can Tương");
        set_picid_1(7304);
        set_picid_2(7304);

        set_level(80);
        set_value(32000);
        set_max_lasting(21599);
        set("ap", 170);
        set("dp", 20);
        set("cp", 205);
        set("sp", 18);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_10; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Kiếm Pháp\"";
}
