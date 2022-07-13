
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Nghênh Phong Trảm");
        set_picid_1(7301);
        set_picid_2(7301);

        set_level(40);
        set_value(12000);
        set_max_lasting(14599);
        set("ap", 92);
        set("dp", 11);
        set("cp", 100);
        set("sp", 10);

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
