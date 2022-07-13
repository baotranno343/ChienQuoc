
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Phi Hồng Hạng Liên");
        set_picid_1(8651);
        set_picid_2(8651);

        set_level(50);
        set_value(27500);
        set_max_lasting(7599);
        set("cp", 0);
        set("pp", 45);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Phi Hồng Hạng Liên";
}
