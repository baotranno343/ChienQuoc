
#include <equip.h>

inherit WEAPON;

// 函数：构造处理
void create()
{
        set_name("Thuý Trúc Bổng");
        set_picid_1(7504);
        set_picid_2(7504);
        set_unit("根");

        set_level(40);
        set_value(6000);
        set_max_lasting(12599);
        set("ap", 84);

        setup();

        set_weapon_type(STICK);
}

// 函数：获取武器级别
int get_weapon_level() { return 4; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Bổng Pháp\"";
}
