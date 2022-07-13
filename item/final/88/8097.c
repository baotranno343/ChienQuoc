
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 8; }

// 函数：成品编号
int get_fin_type() { return 2364; }

// 函数：构造处理
void create()
{
        set_name("Tinh Tú Lý");
        set_picid_1(8807);
        set_picid_2(8807);

        set_level(97);
        set_value(1000);
        set_max_lasting(21899);
        set("ap", 0);
        set("dp", 32);
        set("cp", 0);
        set("pp", 0);
        set("sp", 60);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Tinh Tú Lý";
}
