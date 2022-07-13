
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Bá Giả Nhẫn");
        set_picid_1(7317);
        set_picid_2(7317);

        set_level(90);
        set_value(37000);
        set_max_lasting(22599);
        set("ap", 190);
        set("dp", 23);
        set("cp", 220);
        set("sp", 20);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_11; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Kiếm Pháp\"";
}
