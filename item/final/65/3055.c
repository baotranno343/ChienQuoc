
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 3; }

// 函数：成品编号
int get_fin_type() { return 2146; }

// 函数：构造处理
void create()
{
        set_name("Dương Giác Đầu Khôi");
        set_picid_1(6580);
        set_picid_2(6580);

        set_level(55);
        set_value(8500);
        set_max_lasting(21899);
        set("ap", 0);
        set("dp", 100);
        set("cp", 0);
        set("pp", 33);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Dương Giác Đầu Khôi";
}
