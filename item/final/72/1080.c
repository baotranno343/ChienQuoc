
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 2; }

// 函数：成品编号
int get_fin_type() { return 1038; }

// 函数：构造处理
void create()
{
        set_name("Đại Hạ Long Tước");
        set_picid_1(7212);
        set_picid_2(7212);

        set_level(80);
        set_value(8000);
        set_max_lasting(14099);
        set("ap", 190);
        set("dp", 0);
        set("cp", 0);
        set("pp", 0);

        setup();

        set_weapon_type(BLADE);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_09; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Đao Pháp\"";
}
