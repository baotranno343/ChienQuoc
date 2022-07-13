
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 6; }

// 函数：构造处理
void create()
{
        set_name("Huyết Ẩm");
        set_picid_1(7623);
        set_picid_2(7623);

        set_level(100);
        set_value(54000);
        set_max_lasting(9099);
        set("ap", 200);
        set("dp", 0);
        set("cp", 315);
        set("sp", 0);

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
