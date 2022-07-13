
#include <equip.h>

inherit WEAPON;

// 函数：构造处理
void create()
{
        set_name("Cự Xí Thương");
        set_picid_1(7405);
        set_picid_2(7405);
        set_unit("杆");

        set_level(50);
        set_value(12000);
        set_max_lasting(13599);
        set("ap", 95);
        set("!%", 6);

        setup();

        set_weapon_type(SPEAR);
}

// 函数：获取武器级别
int get_weapon_level() { return 5; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Thương Pháp\"";
}
