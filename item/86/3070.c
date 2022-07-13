
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Quỷ Mị Hạng Liên");
        set_picid_1(8611);
        set_picid_2(8611);

        set_level(70);
        set_value(41500);
        set_max_lasting(8199);
        set("cp", 0);
        set("pp", 65);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Quỷ Mị Hạng Liên";
}
