
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit ARMOR;

// 函数：适用门派
int get_family() { return 4; }

// 函数：成品编号
int get_fin_type() { return 2183; }

// 函数：构造处理
void create()
{
        set_name("Lưu Sa Hành Trang");
        set_picid_1(6115);
        set_picid_2(6115);

        set_level(75);
        set_value(9500);
        set_max_lasting(23899);
        set("ap", 0);
        set("dp", 190);
        set("cp", 0);
        set("pp", 117);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Lưu Sa Hành Trang";
}
