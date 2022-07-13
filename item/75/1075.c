
#include <equip.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 8; }
int is_tieuhuy() { return 2; }
// 函数：构造处理
void create()
{
        set_name("Cổ Phương Côn");
        set_picid_1(6844);
        set_picid_2(6844);

        set_level(75);
        set_value(4000);
        set_max_lasting(1099);
        set("ap+", 10);
        set_item_color(3); //紫色
        setup();

        set_weapon_type(STICK);
}

// 函数：获取武器级别
int get_weapon_level() { return 75; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Bổng Pháp\"";
}

//
string get_tail_desc()
{
        return "Cổ Phương Côn thần kỳ và bí ẩn, hình như ẩn chứa rất nhiều bí mật";
}