
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit MISSILE;

// 函数：适用门派
int get_family() { return 4; }

// 函数：成品编号
int get_fin_type() { return 1047; }

// 函数：构造处理
void create()
{
        set_name("Thấu Hồn Đinh");
        set_picid_1(7119);
        set_picid_2(7119);

        set_level(90);
        set_value(9000);
        set_max_lasting(14599);
        set("ap", 195);
        set("dp", 10);
        set("cp", 0);
        set("pp", 0);

        setup();

        set_weapon_type(THROWING);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_10; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Ám Khí\"";
}
