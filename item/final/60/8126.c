
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit ARMOR;

// 函数：适用门派
int get_family() { return 8; }

// 函数：成品编号
int get_fin_type() { return 2381; }

// 函数：构造处理
void create()
{
        set_name("Thiên Tôn Thánh Bào");
        set_picid_1(6062);
        set_picid_2(6062);

        set_level(126);
        set_value(1000);
        set_max_lasting(27899);
        set("ap", 0);
        set("dp", 190);
        set("cp", 0);
        set("pp", 327);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thiên Tôn Thánh Bào";
}
