
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 6; }

// 函数：成品编号
int get_fin_type() { return 1320; }

// 函数：构造处理
void create()
{
        set_name("Định Hồn Hạng Liên");
        set_picid_1(8655);
        set_picid_2(8655);

        set_level(30);
        set_value(10000);
        set_max_lasting(6099);
        set("ap", 0);
        set("dp", 0);
        set("cp", 65);
        set("pp", 48);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Định Hồn Hạng Liên";
}
