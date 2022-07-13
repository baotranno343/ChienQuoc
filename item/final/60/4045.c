
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit ARMOR;

// 函数：适用门派
int get_family() { return 4; }

// 函数：成品编号
int get_fin_type() { return 2120; }

// 函数：构造处理
void create()
{
        set_name("Vũ Nhung Hành Trang");
        set_picid_1(6003);
        set_picid_2(6003);

        set_level(45);
        set_value(8000);
        set_max_lasting(19899);
        set("ap", 0);
        set("dp", 120);
        set("cp", 0);
        set("pp", 83);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Vũ Nhung Hành Trang";
}
