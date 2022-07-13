
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 1; }

// 函数：成品编号
int get_fin_type() { return 1027; }

// 函数：构造处理
void create()
{
        set_name("Cự Hùng Quyền Sáo");
        set_picid_1(7017);
        set_picid_2(7017);

        set_level(60);
        set_value(6000);
        set_max_lasting(13099);
        set("ap", 145);
        set("dp", 20);
        set("cp", 0);
        set("pp", 0);

        setup();

        set_weapon_type(UNARMED);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_07; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Quyền Pháp\"";
}
