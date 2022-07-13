
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Ngọc Phong Trường Kiếm");
        set_picid_1(7615);
        set_picid_2(7615);

        set_level(130);
        set_value(57000);
        set_max_lasting(26599);
        set("ap", 270);
        set("dp", 37);
        set("cp", 340);
        set("sp", 30);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_14; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Kiếm Pháp\"";
}
