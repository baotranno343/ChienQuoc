
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 6; }

// 函数：成品编号
int get_fin_type() { return 2128; }

// 函数：构造处理
void create()
{
        set_name("Tu Tiên Quán");
        set_picid_1(6558);
        set_picid_2(6558);

        set_level(45);
        set_value(8000);
        set_max_lasting(19899);
        set("ap", 0);
        set("dp", 38);
        set("cp", 0);
        set("pp", 62);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Tu Tiên Quán";
}
