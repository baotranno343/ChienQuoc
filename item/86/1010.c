
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Đồng Hạng Liên");
        set_picid_1(8608);
        set_picid_2(8608);

        set_level(10);
        set_value(1500);
        set_max_lasting(6399);
        set("cp", 0);
        set("pp", 10);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Đồng Hạng Liên";
}
