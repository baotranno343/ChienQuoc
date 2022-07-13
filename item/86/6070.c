
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 6; }

// 函数：构造处理
void create()
{
        set_name("Hoả Văn Hạng Liên");
        set_picid_1(8663);
        set_picid_2(8663);

        set_level(70);
        set_value(53000);
        set_max_lasting(5599);
        set("cp", 130);
        set("pp", 75);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Hoả Văn Hạng Liên";
}
