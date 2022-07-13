
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Liêu Nguyên Hạng Liên");
        set_picid_1(8656);
        set_picid_2(8656);

        set_level(110);
        set_value(77000);
        set_max_lasting(8199);
        set("cp", 0);
        set("pp", 112);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Liêu Nguyên Hạng Liên";
}
