
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 6; }

// 函数：构造处理
void create()
{
        set_name("Phi Thiên Hạng Liên");
        set_picid_1(8614);
        set_picid_2(8614);

        set_level(130);
        set_value(10000);
        set_max_lasting(16099);
        set("cp", 245);
        set("pp", 135);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Phi Thiên Hạng Liên";
}
