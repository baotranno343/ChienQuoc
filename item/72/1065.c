
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Lãnh Nguyệt");
        set_picid_1(7204);
        set_picid_2(7204);

        set_level(65);
        set_value(24000);
        set_max_lasting(18099);
        set("ap", 150);
        set("dp", 0);
        set("cp", 0);
        set("sp", 0);

        setup();

        set_weapon_type(BLADE);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_08; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Đao Pháp\"";
}
