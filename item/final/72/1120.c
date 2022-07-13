
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 2; }

// 函数：成品编号
int get_fin_type() { return 1156; }

// 函数：构造处理
void create()
{
        set_name("Thiên Tuyền Đao");
        set_picid_1(7223);
        set_picid_2(7223);

        set_level(120);
        set_value(12000);
        set_max_lasting(16099);
        set("ap", 280);
        set("dp", 50);
        set("cp", 0);
        set("pp", 0);

        setup();

        set_weapon_type(BLADE);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_13; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Đao Pháp\"";
}
