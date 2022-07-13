
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 2; }

// 函数：成品编号
int get_fin_type() { return 1218; }

// 函数：构造处理
void create()
{
        set_name("Thanh Liễu Hài");
        set_picid_1(8805);
        set_picid_2(8805);

        set_level(20);
        set_value(2000);
        set_max_lasting(8899);
        set("ap", 0);
        set("dp", 14);
        set("cp", 0);
        set("pp", 0);
        set("sp", 14);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thanh Liễu Hài";
}
