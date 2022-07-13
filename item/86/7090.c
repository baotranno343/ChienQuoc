
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 7; }

// 函数：构造处理
void create()
{
        set_name("Thu Nga Hạng Liên");
        set_picid_1(8610);
        set_picid_2(8610);

        set_level(90);
        set_value(71000);
        set_max_lasting(5899);
        set("cp", 170);
        set("pp", 100);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thu Nga Hạng Liên";
}
