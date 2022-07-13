
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 4; }

// 函数：成品编号
int get_fin_type() { return 2130; }

// 函数：构造处理
void create()
{
        set_name("Áp Nhĩ Đầu Cân");
        set_picid_1(6554);
        set_picid_2(6554);

        set_level(45);
        set_value(8000);
        set_max_lasting(19899);
        set("ap", 0);
        set("dp", 65);
        set("cp", 0);
        set("pp", 36);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Áp Nhĩ Đầu Cân";
}
