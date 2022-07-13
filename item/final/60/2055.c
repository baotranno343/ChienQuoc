
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit ARMOR;

// 函数：适用门派
int get_family() { return 2; }

// 函数：成品编号
int get_fin_type() { return 2140; }

// 函数：构造处理
void create()
{
        set_name("Toả Liên Hành Trang");
        set_picid_1(6023);
        set_picid_2(6023);

        set_level(55);
        set_value(8000);
        set_max_lasting(19899);
        set("ap", 0);
        set("dp", 141);
        set("cp", 0);
        set("pp", 87);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Toả Liên Hành Trang";
}
