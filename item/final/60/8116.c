
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit ARMOR;

// 函数：适用门派
int get_family() { return 8; }

// 函数：成品编号
int get_fin_type() { return 2374; }

// 函数：构造处理
void create()
{
        set_name("Long Thần Chiến Giáp");
        set_picid_1(6162);
        set_picid_2(6162);

        set_level(116);
        set_value(1000);
        set_max_lasting(25899);
        set("ap", 0);
        set("dp", 270);
        set("cp", 0);
        set("pp", 167);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Long Thần Chiến Giáp";
}
