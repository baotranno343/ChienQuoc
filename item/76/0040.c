
#include <equip.h>

inherit WEAPON;

// 函数：构造处理
void create()
{
        set_name("Cự Quyết Kiếm");
        set_picid_1(7304);
        set_picid_2(7304);
        set_unit("柄");

        set_level(40);
        set_value(6000);
        set_max_lasting(5599);
        set("ap", 10);
        set("cp", 70);
        set("c!%", 9);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return 4; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Kiếm Pháp\"";
}
