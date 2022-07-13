
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 8; }

// 函数：成品编号
int get_fin_type() { return 1456; }

// 函数：构造处理
void create()
{
        set_name("Phong Thần Hạng Liên");
        set_picid_1(8608);
        set_picid_2(8608);

        set_level(76);
        set_value(999);
        set_max_lasting(10099);
        set("ap", 92);
        set("dp", 0);
        set("cp", 144);
        set("pp", 93);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Phong Thần Hạng Liên";
}
