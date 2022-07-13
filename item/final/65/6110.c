
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 6; }

// 函数：成品编号
int get_fin_type() { return 2100; }

// 函数：构造处理
void create()
{
        set_name("Kiền Vân Chi Quán");
        set_picid_1(6542);
        set_picid_2(6542);

        set_level(110);
        set_value(11000);
        set_max_lasting(26899);
        set("ap", 0);
        set("dp", 77);
        set("cp", 0);
        set("pp", 133);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Kiền Vân Chi Quán";
}
