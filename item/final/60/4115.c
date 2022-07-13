
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit ARMOR;

// 函数：适用门派
int get_family() { return 4; }

// 函数：成品编号
int get_fin_type() { return 2267; }

// 函数：构造处理
void create()
{
        set_name("Chân Vũ Đấu Bồng");
        set_picid_1(6162);
        set_picid_2(6162);

        set_level(115);
        set_value(11500);
        set_max_lasting(27899);
        set("ap", 0);
        set("dp", 270);
        set("cp", 0);
        set("pp", 177);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Chân Vũ Đấu Bồng";
}
