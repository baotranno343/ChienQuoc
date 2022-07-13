
#include <equip.h>

inherit WEAPON;

// 函数：构造处理
void create()
{
        set_name("Trường Sáo Côn");
        set_picid_1(7502);
        set_picid_2(7502);
        set_unit("根");

        set_level(20);
        set_value(1800);
        set_max_lasting(8599);
        set("ap", 48);

        setup();

        set_weapon_type(STICK);
}

// 函数：获取武器级别
int get_weapon_level() { return 2; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Bổng Pháp\"";
}
