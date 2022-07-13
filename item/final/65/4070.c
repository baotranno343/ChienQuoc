
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 4; }

// 函数：成品编号
int get_fin_type() { return 2018; }

// 函数：构造处理
void create()
{
        set_name("Thiên Uy Đầu Cân");
        set_picid_1(6634);
        set_picid_2(6634);

        set_level(70);
        set_value(5500);
        set_max_lasting(14899);
        set("ap", 0);
        set("dp", 115);
        set("cp", 0);
        set("pp", 49);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thiên Uy Đầu Cân";
}
