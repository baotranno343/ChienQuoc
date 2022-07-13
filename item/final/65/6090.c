
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 6; }

// 函数：成品编号
int get_fin_type() { return 2057; }

// 函数：构造处理
void create()
{
        set_name("Phi Long Quán");
        set_picid_1(6578);
        set_picid_2(6578);

        set_level(90);
        set_value(6500);
        set_max_lasting(16899);
        set("ap", 0);
        set("dp", 65);
        set("cp", 0);
        set("pp", 111);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Phi Long Quán";
}
