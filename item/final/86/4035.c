
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 4; }

// 函数：成品编号
int get_fin_type() { return 1323; }

// 函数：构造处理
void create()
{
        set_name("Hoàng Hôn Hạng Liên");
        set_picid_1(8608);
        set_picid_2(8608);

        set_level(35);
        set_value(15000);
        set_max_lasting(6599);
        set("ap", 42);
        set("dp", 0);
        set("cp", 0);
        set("pp", 45);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Hoàng Hôn Hạng Liên";
}
