
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Bạch Kim Hạng Liên");
        set_picid_1(8614);
        set_picid_2(8614);

        set_level(80);
        set_value(48500);
        set_max_lasting(8499);
        set("cp", 0);
        set("pp", 80);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Bạch Kim Hạng Liên";
}
