
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 2; }

// 函数：成品编号
int get_fin_type() { return 2171; }

// 函数：构造处理
void create()
{
        set_name("Hoả Hồng Đầu Cân");
        set_picid_1(6615);
        set_picid_2(6615);

        set_level(65);
        set_value(9000);
        set_max_lasting(22899);
        set("ap", 0);
        set("dp", 116);
        set("cp", 0);
        set("pp", 52);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Hoả Hồng Đầu Cân";
}
