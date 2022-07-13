
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Mặc Ngọc Kiếm");
        set_picid_1(7303);
        set_picid_2(7303);

        set_level(50);
        set_value(17000);
        set_max_lasting(16599);
        set("ap", 110);
        set("dp", 13);
        set("cp", 130);
        set("sp", 12);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_06; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Kiếm Pháp\"";
}
