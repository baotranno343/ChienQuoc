
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit ARMOR;

// 函数：适用门派
int get_family() { return 8; }

// 函数：成品编号
int get_fin_type() { return 2368; }

// 函数：构造处理
void create()
{
        set_name("Kỳ Lân Chiến Y");
        set_picid_1(6058);
        set_picid_2(6058);

        set_level(107);
        set_value(1000);
        set_max_lasting(23899);
        set("ap", 0);
        set("dp", 250);
        set("cp", 0);
        set("pp", 152);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Kỳ Lân Chiến Y";
}
