
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 8; }

// 函数：成品编号
int get_fin_type() { return 2370; }

// 函数：构造处理
void create()
{
        set_name("Kỳ Lân Thần Lý");
        set_picid_1(8811);
        set_picid_2(8811);

        set_level(106);
        set_value(1000);
        set_max_lasting(23899);
        set("ap", 0);
        set("dp", 28);
        set("cp", 0);
        set("pp", 0);
        set("sp", 65);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Kỳ Lân Thần Lý";
}
