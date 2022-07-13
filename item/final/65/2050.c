
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 2; }

// 函数：成品编号
int get_fin_type() { return 1276; }

// 函数：构造处理
void create()
{
        set_name("Hạc Khiếu Đầu Cân");
        set_picid_1(6500);
        set_picid_2(6500);

        set_level(50);
        set_value(4500);
        set_max_lasting(12899);
        set("ap", 0);
        set("dp", 86);
        set("cp", 0);
        set("pp", 42);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Hạc Khiếu Đầu Cân";
}
