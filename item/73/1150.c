
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 9; }

// 函数：构造处理
void create()
{
        set_name("Trấn Yêu Ma Kiếm");
        set_picid_1(6872);
        set_picid_2(6872);

        set_level(150);
        set_value(57000);
        set_max_lasting(76599);
        set("ap+", 270);
		set("c!%+", 30);
		set("double", 600);
        set("dp+", 100);
		set("pp+", 100);
        set("cp+", 540);
		set("cpp", 300);
        set("sp+", 100);
		set_item_color(2);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_14; }

// 函数：获取描述
string get_desc()
{
        return "“Kiếm Pháp” trang bị";
}
