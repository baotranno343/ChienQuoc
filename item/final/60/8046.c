
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit ARMOR;

// 函数：适用门派
int get_family() { return 8; }

// 函数：成品编号
int get_fin_type() { return 2333; }

// 函数：构造处理
void create()
{
        set_name("Truy Phong Pháp Bào");
        set_picid_1(6003);
        set_picid_2(6003);

        set_level(46);
        set_value(1000);
        set_max_lasting(15899);
        set("ap", 0);
        set("dp", 71);
        set("cp", 0);
        set("pp", 127);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Truy Phong Pháp Bào";
}
