
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 5; }

// 函数：成品编号
int get_fin_type() { return 2173; }

// 函数：构造处理
void create()
{
        set_name("Cấp Hành Hài");
        set_picid_1(8807);
        set_picid_2(8807);

        set_level(65);
        set_value(9000);
        set_max_lasting(22899);
        set("ap", 0);
        set("dp", 28);
        set("cp", 0);
        set("pp", 0);
        set("sp", 33);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Cấp Hành Hài";
}
