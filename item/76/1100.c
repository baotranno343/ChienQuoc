
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Trường Không Hạo Nguyệt");
        set_picid_1(7314);
        set_picid_2(7314);

        set_level(100);
        set_value(42000);
        set_max_lasting(23599);
        set("ap", 210);
        set("dp", 26);
        set("cp", 250);
        set("sp", 22);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_12; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Kiếm Pháp\"";
}
