
#include <equip.h>

inherit MISSILE;

// 函数：构造处理
void create()
{
        set_name("Phi Đao");
        set_picid_1(7103);
        set_picid_2(7103);
        set_unit("包");

        set_level(30);
        set_value(3300);
        set_max_lasting(12599);
        set("ap", 37);
        set("t!%", 8);

        setup();

        set_weapon_type(THROWING);
}

// 函数：获取武器级别
int get_weapon_level() { return 3; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Ám Khí\"";
}
