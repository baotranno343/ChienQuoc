
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 3; }

// 函数：成品编号
int get_fin_type() { return 1158; }

// 函数：构造处理
void create()
{
        set_name("Thiên Quyền Côn");
        set_picid_1(7516);
        set_picid_2(7516);

        set_level(120);
        set_value(12000);
        set_max_lasting(16099);
        set("ap", 298);
        set("dp", 50);
        set("cp", 0);
        set("pp", 0);

        setup();

        set_weapon_type(STICK);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_13; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Bổng Pháp\"";
}
