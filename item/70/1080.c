
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit WEAPON;

// 函数：适用门派
int get_family() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Tử Huyết Hộ Thủ");
        set_picid_1(7019);
        set_picid_2(7019);

        set_level(80);
        set_value(32000);
        set_max_lasting(21599);
        set("ap", 195);
        set("dp", 18);
        set("cp", 0);
        set("sp", 0);

        setup();

        set_weapon_type(UNARMED);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_00; }

// 函数：获取描述
string get_desc()
{
        return "Trang bị \"Quyền Pháp\"";
}
