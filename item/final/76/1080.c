
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 9; }

// 函数：成品编号
int get_fin_type() { return 1037; }

// 函数：构造处理
void create()
{
        set_name("Thừa Ảnh Kiếm");
        set_picid_1(7303);
        set_picid_2(7303);

        set_level(80);
        set_value(8000);
        set_max_lasting(14099);
        set("ap", 160);
        set("dp", 9);
        set("cp", 255);
        set("pp", 0);

        setup();

        set_weapon_type(SWORD);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_09; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Kiếm Pháp\"";
}
