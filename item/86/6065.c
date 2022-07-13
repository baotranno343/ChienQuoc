
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 6; }

// 函数：构造处理
void create()
{
        set_name("Tuyệt Tình Chi Liên");
        set_picid_1(8659);
        set_picid_2(8659);

        set_level(65);
        set_value(48500);
        set_max_lasting(5499);
        set("cp", 120);
        set("pp", 70);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Tuyệt Tình Chi Liên";
}
