
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit ARMOR;

// 函数：适用门派
int get_family() { return 2; }

// 函数：成品编号
int get_fin_type() { return 2224; }

// 函数：构造处理
void create()
{
        set_name("Nghê Thường Hành Trang");
        set_picid_1(6082);
        set_picid_2(6082);

        set_level(95);
        set_value(10000);
        set_max_lasting(24899);
        set("ap", 0);
        set("dp", 221);
        set("cp", 0);
        set("pp", 137);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Nghê Thường Hành Trang";
}
