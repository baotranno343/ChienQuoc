
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 8; }

// 函数：成品编号
int get_fin_type() { return 1458; }

// 函数：构造处理
void create()
{
        set_name("Thần Uy Hạng Liên");
        set_picid_1(8610);
        set_picid_2(8610);

        set_level(96);
        set_value(999);
        set_max_lasting(15099);
        set("ap", 122);
        set("dp", 0);
        set("cp", 190);
        set("pp", 123);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thần Uy Hạng Liên";
}
