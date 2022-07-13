
#include <equip.h>

inherit MISSILE;

// 函数：构造处理
void create()
{
        set_name("Phi Hoàng Thạch");
        set_picid_1(7104);
        set_picid_2(7104);
        set_unit("袋");

        set_level(40);
        set_value(6000);
        set_max_lasting(14599);
        set("ap", 47);
        set("t!%", 9);

        setup();

        set_weapon_type(THROWING);
}

// 函数：获取武器级别
int get_weapon_level() { return 4; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Ám Khí\"";
}
