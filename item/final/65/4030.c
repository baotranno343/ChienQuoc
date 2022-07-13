
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 4; }

// 函数：成品编号
int get_fin_type() { return 1234; }

// 函数：构造处理
void create()
{
        set_name("Thiên Thuỷ Đầu Cân");
        set_picid_1(6505);
        set_picid_2(6505);

        set_level(30);
        set_value(3000);
        set_max_lasting(9099);
        set("ap", 0);
        set("dp", 35);
        set("cp", 0);
        set("pp", 26);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thiên Thuỷ Đầu Cân";
}
