
#include <equip.h>

inherit WEAPON;

// 函数：构造处理
void create()
{
        set_name("Thứ Truỳ Thương");
        set_picid_1(7402);
        set_picid_2(7402);
        set_unit("杆");

        set_level(20);
        set_value(1800);
        set_max_lasting(8599);
        set("ap", 44);
        set("!%", 3);

        setup();

        set_weapon_type(SPEAR);
}

// 函数：获取武器级别
int get_weapon_level() { return 2; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Thương Pháp\"";
}
