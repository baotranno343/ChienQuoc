
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Kì Đảo Hạng Liên");
        set_picid_1(8654);
        set_picid_2(8654);

        set_level(100);
        set_value(62500);
        set_max_lasting(9099);
        set("cp", 0);
        set("pp", 95);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Kì Đảo Hạng Liên";
}
