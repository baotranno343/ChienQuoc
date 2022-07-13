
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Hoả Diễm Chi Liên");
        set_picid_1(8612);
        set_picid_2(8612);

        set_level(45);
        set_value(26600);
        set_max_lasting(6199);
        set("cp", 0);
        set("pp", 47);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Hoả Diễm Chi Liên";
}
