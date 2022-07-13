
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit ARMOR;

// 函数：适用门派
int get_family() { return 4; }

// 函数：成品编号
int get_fin_type() { return 1286; }

// 函数：构造处理
void create()
{
        set_name("Kim Ti Hành Trang");
        set_picid_1(6058);
        set_picid_2(6058);

        set_level(60);
        set_value(4500);
        set_max_lasting(12899);
        set("ap", 0);
        set("dp", 150);
        set("cp", 0);
        set("pp", 105);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Kim Ti Hành Trang";
}
