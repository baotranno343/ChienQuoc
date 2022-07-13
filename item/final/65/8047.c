
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 8; }

// 函数：成品编号
int get_fin_type() { return 2336; }

// 函数：构造处理
void create()
{
        set_name("Truy Phong Chiến Khôi");
        set_picid_1(6560);
        set_picid_2(6560);

        set_level(47);
        set_value(1000);
        set_max_lasting(15899);
        set("ap", 0);
        set("dp", 85);
        set("cp", 0);
        set("pp", 27);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Truy Phong Chiến Khôi";
}
