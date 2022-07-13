
#include <equip.h>

inherit MISSILE;

// 函数：构造处理
void create()
{
        set_name("Ngũ Lăng Tiêu");
        set_picid_1(7105);
        set_picid_2(7105);
        set_unit("把");

        set_level(50);
        set_value(12000);
        set_max_lasting(15099);
        set("ap+", 57);
        set("t!%+", 10);

        setup();

        set_weapon_type(THROWING);
}

// 函数：获取武器级别
int get_weapon_level() { return 5; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Ám Khí\"";
}
