
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Minh Quang Thị Hồn");
        set_picid_1(7616);
        set_picid_2(7616);

        set_level(110);
        set_value(47000);
        set_max_lasting(24599);
        set("ap", 230);
        set("dp", 29);
        set("cp", 280);
        set("sp", 24);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_13; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Kiếm Pháp\"";
}
