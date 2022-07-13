
#include <equip.h>

inherit WEAPON;

// 函数：构造处理
void create()
{
        set_name("Câu Liêm Thương");
        set_picid_1(7404);
        set_picid_2(7404);
        set_unit("杆");

        set_level(40);
        set_value(6000);
        set_max_lasting(12599);
        set("ap", 78);
        set("!%", 5);

        setup();

        set_weapon_type(SPEAR);
}

// 函数：获取武器级别
int get_weapon_level() { return 4; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Thương Pháp\"";
}
