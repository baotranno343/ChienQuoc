
// 自动生成：/make/weapon/make72b

#include <equip.h>
#include <level.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 3; }

// 函数：成品编号
int get_fin_type() { return 2054; }

// 函数：构造处理
void create()
{
        set_name("Phi Thiên Chiến Khôi");
        set_picid_1(6562);
        set_picid_2(6562);

        set_level(90);
        set_value(6500);
        set_max_lasting(16899);
        set("ap", 0);
        set("dp", 170);
        set("cp", 0);
        set("pp", 50);
        set("sp", 0);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Phi Thiên Chiến Khôi";
}
