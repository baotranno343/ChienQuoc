
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 5; }

// 函数：构造处理
void create()
{
        set_name("Thần Phong Hạng Liên");
        set_picid_1(8606);
        set_picid_2(8606);

        set_level(90);
        set_value(71000);
        set_max_lasting(5899);
        set("cp", 168);
        set("pp", 96);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thần Phong Hạng Liên";
}
