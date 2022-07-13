
#include <equip.h>

inherit MISSILE;

// 函数：构造处理
void create()
{
        set_name("Toái Thạch Tử");
        set_picid_1(7100);
        set_picid_2(7100);
        set_unit("袋");

        set_level(0);
        set_value(450);
        set_max_lasting(6099);
        set("ap", 7);
        set("t!%", 5);

        setup();

        set_weapon_type(THROWING);
}

// 函数：获取武器级别
int get_weapon_level() { return 0; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Ám Khí\"";
}
