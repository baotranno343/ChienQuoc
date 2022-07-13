
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 7; }

// 函数：构造处理
void create()
{
        set_name("Hàn Lôi Hạng Liên");
        set_picid_1(8659);
        set_picid_2(8659);

        set_level(70);
        set_value(53000);
        set_max_lasting(5599);
        set("cp", 130);
        set("pp", 80);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Hàn Lôi Hạng Liên";
}
