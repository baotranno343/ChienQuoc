
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 2; }

// 函数：成品编号
int get_fin_type() { return 2129; }

// 函数：构造处理
void create()
{
        set_name("Ngạ Nhung Đầu Cân");
        set_picid_1(6600);
        set_picid_2(6600);

        set_level(45);
        set_value(8000);
        set_max_lasting(19899);
        set("ap", 0);
        set("dp", 76);
        set("cp", 0);
        set("pp", 39);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Ngạ Nhung Đầu Cân";
}
