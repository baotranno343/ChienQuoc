
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 5; }

// 函数：构造处理
void create()
{
        set_name("Ngọc Lăng Hạng Liên");
        set_picid_1(8652);
        set_picid_2(8652);

        set_level(30);
        set_value(17000);
        set_max_lasting(4999);
        set("cp", 48);
        set("pp", 36);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Ngọc Lăng Hạng Liên";
}
