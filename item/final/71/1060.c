
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit MISSILE;

// 函数：适用门派
int get_family() { return 4; }

// 函数：成品编号
int get_fin_type() { return 1028; }

// 函数：构造处理
void create()
{
        set_name("Truy Tâm Tiễn");
        set_picid_1(7103);
        set_picid_2(7103);

        set_level(60);
        set_value(6000);
        set_max_lasting(13099);
        set("ap", 129);
        set("dp", 155);
        set("cp", 0);
        set("pp", 0);

        setup();

        set_weapon_type(THROWING);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_07; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Ám Khí\"";
}
