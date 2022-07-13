
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Phi Hổ Hạng Liên");
        set_picid_1(8652);
        set_picid_2(8652);

        set_level(130);
        set_value(10000);
        set_max_lasting(16099);
        set("ap", 130);
        set("cp", 0);
        set("pp", 130);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Phi Hổ Hạng Liên";
}
