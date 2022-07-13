
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 4; }

// 函数：成品编号
int get_fin_type() { return 1296; }

// 函数：构造处理
void create()
{
        set_name("Kim Ti Đầu Cân");
        set_picid_1(6615);
        set_picid_2(6615);

        set_level(60);
        set_value(5000);
        set_max_lasting(13899);
        set("ap", 0);
        set("dp", 95);
        set("cp", 0);
        set("pp", 44);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Kim Ti Đầu Cân";
}
