
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit ARMOR;

// 函数：适用门派
int get_family() { return 2; }

// 函数：成品编号
int get_fin_type() { return 2070; }

// 函数：构造处理
void create()
{
        set_name("Phá Vân Hành Trang");
        set_picid_1(6038);
        set_picid_2(6038);

        set_level(100);
        set_value(7000);
        set_max_lasting(17899);
        set("ap", 0);
        set("dp", 221);
        set("cp", 0);
        set("pp", 155);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Phá Vân Hành Trang";
}
