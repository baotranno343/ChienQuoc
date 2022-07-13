
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit ARMOR;

// 函数：适用门派
int get_family() { return 7; }

// 函数：成品编号
int get_fin_type() { return 2072; }

// 函数：构造处理
void create()
{
        set_name("Sí Văn Chiến Bào");
        set_picid_1(6142);
        set_picid_2(6142);

        set_level(100);
        set_value(7000);
        set_max_lasting(17899);
        set("ap", 0);
        set("dp", 164);
        set("cp", 0);
        set("pp", 264);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Sí Văn Chiến Bào";
}
