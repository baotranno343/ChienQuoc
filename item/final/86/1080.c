
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 1; }

// 函数：成品编号
int get_fin_type() { return 1384; }

// 函数：构造处理
void create()
{
        set_name("Chân Vũ Hạng Liên");
        set_picid_1(8608);
        set_picid_2(8608);

        set_level(80);
        set_value(20000);
        set_max_lasting(20099);
        set("ap", 101);
        set("dp", 0);
        set("cp", 0);
        set("pp", 84);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Chân Vũ Hạng Liên";
}
