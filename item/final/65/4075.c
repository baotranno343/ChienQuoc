
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 4; }

// 函数：成品编号
int get_fin_type() { return 2193; }

// 函数：构造处理
void create()
{
        set_name("Linh Hồn Đầu Cân");
        set_picid_1(6634);
        set_picid_2(6634);

        set_level(75);
        set_value(9500);
        set_max_lasting(23899);
        set("ap", 0);
        set("dp", 125);
        set("cp", 0);
        set("pp", 52);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Linh Hồn Đầu Cân";
}
