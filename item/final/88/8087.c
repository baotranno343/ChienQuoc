
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 8; }

// 函数：成品编号
int get_fin_type() { return 2359; }

// 函数：构造处理
void create()
{
        set_name("Thần Uy Chiến Ngoa");
        set_picid_1(8811);
        set_picid_2(8811);

        set_level(87);
        set_value(1000);
        set_max_lasting(19899);
        set("ap", 0);
        set("dp", 39);
        set("cp", 0);
        set("pp", 0);
        set("sp", 45);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thần Uy Chiến Ngoa";
}
