
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 7; }

// 函数：成品编号
int get_fin_type() { return 2148; }

// 函数：构造处理
void create()
{
        set_name("Húc Quang Quán");
        set_picid_1(6578);
        set_picid_2(6578);

        set_level(55);
        set_value(8500);
        set_max_lasting(21899);
        set("ap", 0);
        set("dp", 47);
        set("cp", 0);
        set("pp", 73);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Húc Quang Quán";
}
