
#include <equip.h>

inherit MISSILE;

// 函数：构造处理
void create()
{
        set_name("Liễu Điệp Tiêu");
        set_picid_1(7102);
        set_picid_2(7102);
        set_unit("包");

        set_level(20);
        set_value(1800);
        set_max_lasting(11099);
        set("ap", 27);
        set("t!%", 7);

        setup();

        set_weapon_type(THROWING);
}

// 函数：获取武器级别
int get_weapon_level() { return 2; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Ám Khí\"";
}
