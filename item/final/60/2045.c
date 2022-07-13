
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit ARMOR;

// 函数：适用门派
int get_family() { return 2; }

// 函数：成品编号
int get_fin_type() { return 2119; }

// 函数：构造处理
void create()
{
        set_name("Nhuyễn Bì Hành Trang");
        set_picid_1(6003);
        set_picid_2(6003);

        set_level(45);
        set_value(7500);
        set_max_lasting(18899);
        set("ap", 0);
        set("dp", 111);
        set("cp", 0);
        set("pp", 73);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Nhuyễn Bì Hành Trang";
}
