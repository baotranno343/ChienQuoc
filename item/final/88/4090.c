
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 4; }

// 函数：成品编号
int get_fin_type() { return 2066; }

// 函数：构造处理
void create()
{
        set_name("Phượng Vũ Ngoa");
        set_picid_1(8807);
        set_picid_2(8807);

        set_level(90);
        set_value(7000);
        set_max_lasting(17899);
        set("ap", 0);
        set("dp", 25);
        set("cp", 0);
        set("pp", 0);
        set("sp", 50);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Phượng Vũ Ngoa";
}
