
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit ARMOR;

// 函数：适用门派
int get_family() { return 8; }

// 函数：成品编号
int get_fin_type() { return 2375; }

// 函数：构造处理
void create()
{
        set_name("Long Thần Thánh Bào");
        set_picid_1(6162);
        set_picid_2(6162);

        set_level(117);
        set_value(1000);
        set_max_lasting(25899);
        set("ap", 0);
        set("dp", 175);
        set("cp", 0);
        set("pp", 302);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Long Thần Thánh Bào";
}
