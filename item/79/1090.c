
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 7; }

// 函数：构造处理
void create()
{
        set_name("Ngọc Văn Kiếm");
        set_picid_1(7314);
        set_picid_2(7314);

        set_level(90);
        set_value(48000);
        set_max_lasting(8599);
        set("ap", 185);
        set("dp", 0);
        set("cp", 285);
        set("sp", 0);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_11; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Kiếm Pháp\"";
}
