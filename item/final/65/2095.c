
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 2; }

// 函数：成品编号
int get_fin_type() { return 2234; }

// 函数：构造处理
void create()
{
        set_name("Nghê Thường Đầu Cân");
        set_picid_1(6625);
        set_picid_2(6625);

        set_level(95);
        set_value(10500);
        set_max_lasting(25899);
        set("ap", 0);
        set("dp", 176);
        set("cp", 0);
        set("pp", 67);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Nghê Thường Đầu Cân";
}
