
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 2; }

// 函数：成品编号
int get_fin_type() { return 1297; }

// 函数：构造处理
void create()
{
        set_name("Đạp Thanh Đầu Cân");
        set_picid_1(6634);
        set_picid_2(6634);

        set_level(60);
        set_value(5000);
        set_max_lasting(13899);
        set("ap", 0);
        set("dp", 106);
        set("cp", 0);
        set("pp", 47);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Đạp Thanh Đầu Cân";
}
