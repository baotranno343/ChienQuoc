
#include <equip.h>

inherit WEAPON;

// 函数：构造处理
void create()
{
        set_name("Lộc Bì Quyền Sáo");
        set_picid_1(7002);
        set_picid_2(7002);
        set_unit("双");

        set_level(20);
        set_value(1800);
        set_max_lasting(8599);
        set("ap", 36);
        set("!%", 12);

        setup();

        set_weapon_type(UNARMED);
}

// 函数：获取武器级别
int get_weapon_level() { return 2; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Quyền Pháp\"";
}
