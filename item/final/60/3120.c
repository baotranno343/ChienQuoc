
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit ARMOR;

// 函数：适用门派
int get_family() { return 3; }

// 函数：成品编号
int get_fin_type() { return 2286; }

// 函数：构造处理
void create()
{
        set_name("Tinh Thần Chiến Giáp");
        set_picid_1(6182);
        set_picid_2(6182);

        set_level(120);
        set_value(12000);
        set_max_lasting(28899);
        set("ap", 0);
        set("dp", 265);
        set("cp", 0);
        set("pp", 185);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Tinh Thần Chiến Giáp";
}
