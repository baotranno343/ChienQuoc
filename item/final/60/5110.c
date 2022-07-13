
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit ARMOR;

// 函数：适用门派
int get_family() { return 5; }

// 函数：成品编号
int get_fin_type() { return 2093; }

// 函数：构造处理
void create()
{
        set_name("Kiền Vân Chiến Bào");
        set_picid_1(6162);
        set_picid_2(6162);

        set_level(110);
        set_value(11000);
        set_max_lasting(26899);
        set("ap", 0);
        set("dp", 185);
        set("cp", 0);
        set("pp", 286);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Kiền Vân Chiến Bào";
}
