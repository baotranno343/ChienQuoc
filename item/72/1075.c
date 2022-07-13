
#include <equip.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 8; }
int is_tieuhuy() { return 2; }
// 函数：构造处理
void create()
{
        set_name("Kim Đao");
        set_picid_1(6803);
        set_picid_2(6803);

        set_level(75);
        set_value(4000);
        set_max_lasting(1099);
        set("ap+", 10);
        set_item_color(3); //紫色
        setup();

        set_weapon_type(BLADE);
}

// 函数：获取武器级别
int get_weapon_level() { return 75; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Đao Pháp\"";
}

//
string get_tail_desc()
{
        return "Kim Đao thần bí, hình như chứa đựng bí mật gì đó";
}