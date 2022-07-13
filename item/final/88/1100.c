
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 1; }

// 函数：成品编号
int get_fin_type() { return 2087; }

// 函数：构造处理
void create()
{
        set_name("Long Lân Ngoa");
        set_picid_1(8812);
        set_picid_2(8812);

        set_level(100);
        set_value(7500);
        set_max_lasting(18899);
        set("ap", 0);
        set("dp", 34);
        set("cp", 0);
        set("pp", 0);
        set("sp", 44);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Long Lân Ngoa";
}
