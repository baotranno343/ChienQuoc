
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 5; }

// 函数：成品编号
int get_fin_type() { return 2083; }

// 函数：构造处理
void create()
{
        set_name("Hỗn Lôi Hài");
        set_picid_1(8811);
        set_picid_2(8811);

        set_level(100);
        set_value(7500);
        set_max_lasting(18899);
        set("ap", 0);
        set("dp", 45);
        set("cp", 0);
        set("pp", 0);
        set("sp", 50);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Hỗn Lôi Hài";
}
