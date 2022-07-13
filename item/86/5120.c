
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 5; }

// 函数：构造处理
void create()
{
        set_name("Thị Tôn Hạng Liên");
        set_picid_1(8664);
        set_picid_2(8664);

        set_level(120);
        set_value(98000);
        set_max_lasting(6399);
        set("cp", 228);
        set("pp", 126);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thị Tôn Hạng Liên";
}
