
#include <equip.h>

inherit WEAPON;

// 函数：构造处理
void create()
{
        set_name("Truy Phong Kiếm");
        set_picid_1(7303);
        set_picid_2(7303);
        set_unit("柄");

        set_level(30);
        set_value(3300);
        set_max_lasting(5099);
        set("ap", 8);
        set("cp", 55);
        set("c!%", 8);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return 3; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Kiếm Pháp\"";
}
