
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 5; }

// 函数：成品编号
int get_fin_type() { return 1423; }

// 函数：构造处理
void create()
{
        set_name("Long Hồn Hạng Liên");
        set_picid_1(8655);
        set_picid_2(8655);

        set_level(105);
        set_value(20000);
        set_max_lasting(45099);
        set("ap", 0);
        set("dp", 0);
        set("cp", 210);
        set("pp", 117);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Long Hồn Hạng Liên";
}
