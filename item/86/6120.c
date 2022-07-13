
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 6; }

// 函数：构造处理
void create()
{
        set_name("Can Khôn Hạng Liên");
        set_picid_1(8663);
        set_picid_2(8663);

        set_level(120);
        set_value(98000);
        set_max_lasting(6399);
        set("cp", 230);
        set("pp", 125);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Can Khôn Hạng Liên";
}
