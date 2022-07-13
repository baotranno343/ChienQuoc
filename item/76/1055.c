
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Huyền Minh Kiếm");
        set_picid_1(7303);
        set_picid_2(7303);

        set_level(55);
        set_value(19000);
        set_max_lasting(17599);
        set("ap", 121);
        set("dp", 14);
        set("cp", 145);
        set("sp", 13);

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
