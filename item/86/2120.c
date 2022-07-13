
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Ngọc Tôn Hạng Liên");
        set_picid_1(8657);
        set_picid_2(8657);

        set_level(120);
        set_value(76500);
        set_max_lasting(9699);
        set("cp", 0);
        set("pp", 125);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Ngọc Tôn Hạng Liên";
}
