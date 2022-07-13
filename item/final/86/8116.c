
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 8; }

// 函数：成品编号
int get_fin_type() { return 1460; }

// 函数：构造处理
void create()
{
        set_name("Long Thần Hạng Liên");
        set_picid_1(0100);
        set_picid_2(0100);

        set_level(116);
        set_value(999);
        set_max_lasting(26099);
        set("ap", 152);
        set("dp", 0);
        set("cp", 236);
        set("pp", 153);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Long Thần Hạng Liên";
}
