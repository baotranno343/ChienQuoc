
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 7; }

// 函数：构造处理
void create()
{
        set_name("Hàn Thanh Kiếm");
        set_picid_1(7315);
        set_picid_2(7315);

        set_level(50);
        set_value(24000);
        set_max_lasting(6599);
        set("ap", 105);
        set("dp", 0);
        set("cp", 165);
        set("sp", 0);

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
