
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Hổ Xí Hạng Liên");
        set_picid_1(8601);
        set_picid_2(8601);

        set_level(45);
        set_value(24000);
        set_max_lasting(7399);
        set("cp", 0);
        set("pp", 45);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Hổ Xí Hạng Liên";
}
