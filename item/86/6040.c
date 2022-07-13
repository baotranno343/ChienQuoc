
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 6; }

// 函数：构造处理
void create()
{
        set_name("Thủy Chi Hạng Liên");
        set_picid_1(8652);
        set_picid_2(8652);

        set_level(40);
        set_value(26000);
        set_max_lasting(5199);
        set("cp", 70);
        set("pp", 45);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thủy Chi Hạng Liên";
}
