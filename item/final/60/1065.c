
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit ARMOR;

// 函数：适用门派
int get_family() { return 1; }

// 函数：成品编号
int get_fin_type() { return 2159; }

// 函数：构造处理
void create()
{
        set_name("Kim Ty Giáp");
        set_picid_1(6038);
        set_picid_2(6038);

        set_level(65);
        set_value(8500);
        set_max_lasting(21899);
        set("ap", 0);
        set("dp", 160);
        set("cp", 0);
        set("pp", 95);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Kim Ty Giáp";
}
