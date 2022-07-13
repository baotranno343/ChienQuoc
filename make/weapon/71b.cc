
// 自动生成：/make/weapon/make71b

#include <equip.h>
#include <level.h>

inherit MISSILE;

// 函数：构造处理
void create()
{
        set_name("%s");
        set_picid_1(%04d);
        set_picid_2(%04d);

        set_level(%d);
        set_value(%d);
        set_max_lasting(%d);
        set("ap", %d);
        set("dp", %d);
        set("cp", %d);
        set("sp", %d);

        setup();

        set_weapon_type(THROWING);
}

// 函数：获取武器级别
int get_weapon_level() { return LEVEL_%02d; }

// 函数：获取描述
string get_desc()
{
        return "“暗器”装备";
}
