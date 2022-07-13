
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit ARMOR;

// 函数：适用门派
int get_family() { return 3; }

// 函数：成品编号
int get_fin_type() { return 2202; }

// 函数：构造处理
void create()
{
        set_name("Hoàng Kim Chiến Khải");
        set_picid_1(6062);
        set_picid_2(6062);

        set_level(85);
        set_value(9500);
        set_max_lasting(23899);
        set("ap", 0);
        set("dp", 205);
        set("cp", 0);
        set("pp", 122);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Hoàng Kim Chiến Khải";
}
