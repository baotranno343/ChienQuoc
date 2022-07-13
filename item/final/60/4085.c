
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit ARMOR;

// 函数：适用门派
int get_family() { return 4; }

// 函数：成品编号
int get_fin_type() { return 2204; }

// 函数：构造处理
void create()
{
        set_name("Hoàn Vụ Hành Trang");
        set_picid_1(6013);
        set_picid_2(6013);

        set_level(85);
        set_value(10000);
        set_max_lasting(24899);
        set("ap", 0);
        set("dp", 210);
        set("cp", 0);
        set("pp", 132);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Hoàn Vụ Hành Trang";
}
