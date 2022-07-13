
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit ARMOR;

// 函数：适用门派
int get_family() { return 2; }

// 函数：成品编号
int get_fin_type() { return 2028; }

// 函数：构造处理
void create()
{
        set_name("Phiên Vân Hành Trang");
        set_picid_1(6013);
        set_picid_2(6013);

        set_level(80);
        set_value(6000);
        set_max_lasting(15899);
        set("ap", 0);
        set("dp", 181);
        set("cp", 0);
        set("pp", 125);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Phiên Vân Hành Trang";
}
