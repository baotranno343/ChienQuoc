
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 7; }

// 函数：成品编号
int get_fin_type() { return 2169; }

// 函数：构造处理
void create()
{
        set_name("Thanh Vân Quán");
        set_picid_1(6538);
        set_picid_2(6538);

        set_level(65);
        set_value(9000);
        set_max_lasting(22899);
        set("ap", 0);
        set("dp", 53);
        set("cp", 0);
        set("pp", 84);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thanh Vân Quán";
}
