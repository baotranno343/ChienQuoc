
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 8; }

// 函数：成品编号
int get_fin_type() { return 2341; }

// 函数：构造处理
void create()
{
        set_name("Thần Hành Hài");
        set_picid_1(8808);
        set_picid_2(8808);

        set_level(56);
        set_value(1000);
        set_max_lasting(16899);
        set("ap", 0);
        set("dp", 25);
        set("cp", 0);
        set("pp", 0);
        set("sp", 30);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thần Hành Hài";
}
