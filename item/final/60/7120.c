
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit ARMOR;

// 函数：适用门派
int get_family() { return 7; }

// 函数：成品编号
int get_fin_type() { return 2290; }

// 函数：构造处理
void create()
{
        set_name("Khâm Thiên Chiến Bào");
        set_picid_1(6062);
        set_picid_2(6062);

        set_level(120);
        set_value(12000);
        set_max_lasting(28899);
        set("ap", 0);
        set("dp", 194);
        set("cp", 0);
        set("pp", 314);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Khâm Thiên Chiến Bào";
}
