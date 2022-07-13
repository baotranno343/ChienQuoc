
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 5; }

// 函数：成品编号
int get_fin_type() { return 1430; }

// 函数：构造处理
void create()
{
        set_name("Long Ngâm Hạng Liên");
        set_picid_1(8608);
        set_picid_2(8608);

        set_level(110);
        set_value(20000);
        set_max_lasting(50099);
        set("ap", 0);
        set("dp", 0);
        set("cp", 220);
        set("pp", 122);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Long Ngâm Hạng Liên";
}
