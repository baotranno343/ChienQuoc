
#include <equip.h>

inherit WEAPON;

// 函数：构造处理
void create()
{
        set_name("Mộc Kiếm");
        set_picid_1(7300);
        set_picid_2(7300);
        set_unit("柄");

        set_level(0);
        set_value(450);
        set_max_lasting(4599);
        set("ap", 8);
        set("!%", 7);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return 0; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị “Kiếm Pháp”";
}
