
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 4; }

// 函数：成品编号
int get_fin_type() { return 2081; }

// 函数：构造处理
void create()
{
        set_name("Nhiếp Hồn Đầu Cân");
        set_picid_1(6556);
        set_picid_2(6556);

        set_level(100);
        set_value(7500);
        set_max_lasting(18899);
        set("ap", 0);
        set("dp", 175);
        set("cp", 0);
        set("pp", 64);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Nhiếp Hồn Đầu Cân";
}
