
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit ARMOR;

// 函数：适用门派
int get_family() { return 7; }

// 函数：成品编号
int get_fin_type() { return 1288; }

// 函数：构造处理
void create()
{
        set_name("Triệt Vân Bào");
        set_picid_1(6025);
        set_picid_2(6025);

        set_level(60);
        set_value(4500);
        set_max_lasting(12899);
        set("ap", 0);
        set("dp", 104);
        set("cp", 0);
        set("pp", 164);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Triệt Vân Bào";
}
