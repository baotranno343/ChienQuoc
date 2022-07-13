
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 5; }

// 函数：成品编号
int get_fin_type() { return 1251; }

// 函数：构造处理
void create()
{
        set_name("Hoán Vân Quán");
        set_picid_1(6558);
        set_picid_2(6558);

        set_level(40);
        set_value(4000);
        set_max_lasting(9899);
        set("ap", 0);
        set("dp", 37);
        set("cp", 0);
        set("pp", 57);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Hoán Vân Quán";
}
