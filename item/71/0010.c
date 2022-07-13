
#include <equip.h>

inherit MISSILE;

// 函数：构造处理
void create()
{
        set_name("Mai Hoa Châm");
        set_picid_1(7101);
        set_picid_2(7101);
        set_unit("包");

        set_level(10);
        set_value(900);
        set_max_lasting(8599);
        set("ap", 17);
        set("t!%", 6);

        setup();

        set_weapon_type(THROWING);
}

// 函数：获取武器级别
int get_weapon_level() { return 1; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Ám Khí\"";
}
