
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 7; }

// 函数：构造处理
void create()
{
        set_name("Quỷ Cốc Hạng Liên");
        set_picid_1(8663);
        set_picid_2(8663);

        set_level(130);
        set_value(10000);
        set_max_lasting(16099);
        set("cp", 245);
        set("pp", 140);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Quỷ Cốc Hạng Liên";
}
