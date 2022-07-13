
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 3; }

// 函数：成品编号
int get_fin_type() { return 1262; }

// 函数：构造处理
void create()
{
        set_name("Phá Địch Ngoa");
        set_picid_1(8805);
        set_picid_2(8805);

        set_level(40);
        set_value(4000);
        set_max_lasting(9899);
        set("ap", 0);
        set("dp", 21);
        set("cp", 0);
        set("pp", 0);
        set("sp", 19);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Phá Địch Ngoa";
}
