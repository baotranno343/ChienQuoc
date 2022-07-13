
#include <equip.h>

inherit WEAPON;

// 函数：构造处理
void create()
{
        set_name("Tùng Văn Kiếm");
        set_picid_1(7302);
        set_picid_2(7302);
        set_unit("柄");

        set_level(20);
        set_value(1800);
        set_max_lasting(4099);
        set("ap", 6);
        set("cp", 40);
        set("c!%", 7);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return 2; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Kiếm Pháp\"";
}
