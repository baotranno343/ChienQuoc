
#include <equip.h>

inherit WEAPON;

// 函数：构造处理
void create()
{
        set_name("Côn Ngô Kiếm");
        set_picid_1(7305);
        set_picid_2(7305);
        set_unit("柄");

        set_level(50);
        set_value(12000);
        set_max_lasting(13599);
        set("ap", 78);
        set("cp", 78);
     //   set("!%", 12);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return 5; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị “Kiếm Pháp”";
}
