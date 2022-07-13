
#include <equip.h>

inherit WEAPON;

// 函数：构造处理
void create()
{
        set_name("Trường Kích");
        set_picid_1(7403);
        set_picid_2(7403);
        set_unit("杆");

        set_level(30);
        set_value(3300);
        set_max_lasting(11099);
        set("ap", 61);
        set("!%", 4);

        setup();

        set_weapon_type(SPEAR);
}

// 函数：获取武器级别
int get_weapon_level() { return 3; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Thương Pháp\"";
}
