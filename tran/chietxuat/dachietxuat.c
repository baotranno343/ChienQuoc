
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_item_color() { return 3; }
int get_family() { return 8; }
int is_dachietxuat() { return 1; }
// 函数：构造处理
void create()
{
        set_name("Đá Chiết Xuất");
        set_picid_1(7200);
        set_picid_2(7200);

        set_level(0);
        set_value(450);
        set_max_lasting(1000);

        setup();

        // set_weapon_type(BLADE);
}

// 函数：获取武器级别
// int get_weapon_level() { return LEVEL_01; }

// 函数：获取描述
string get_desc()
{
        return "Đá Chiết Xuất";
}
