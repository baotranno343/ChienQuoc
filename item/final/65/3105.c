
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 3; }

// 函数：成品编号
int get_fin_type() { return 2251; }

// 函数：构造处理
void create()
{
        set_name("Vong Hồn Chi Khôi");
        set_picid_1(6582);
        set_picid_2(6582);

        set_level(105);
        set_value(11000);
        set_max_lasting(26899);
        set("ap", 0);
        set("dp", 200);
        set("cp", 0);
        set("pp", 58);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Vong Hồn Chi Khôi";
}
