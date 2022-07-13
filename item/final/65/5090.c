
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 5; }

// 函数：成品编号
int get_fin_type() { return 2056; }

// 函数：构造处理
void create()
{
        set_name("Xích Vân Quán");
        set_picid_1(6578);
        set_picid_2(6578);

        set_level(90);
        set_value(6500);
        set_max_lasting(16899);
        set("ap", 0);
        set("dp", 67);
        set("cp", 0);
        set("pp", 111);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Xích Vân Quán";
}
