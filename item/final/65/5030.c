
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 5; }

// 函数：成品编号
int get_fin_type() { return 1232; }

// 函数：构造处理
void create()
{
        set_name("Ngọc Lộ Quán");
        set_picid_1(6538);
        set_picid_2(6538);

        set_level(30);
        set_value(3000);
        set_max_lasting(9099);
        set("ap", 0);
        set("dp", 31);
        set("cp", 0);
        set("pp", 46);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Ngọc Lộ Quán";
}
