
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Toàn Phong Hạng Liên");
        set_picid_1(8611);
        set_picid_2(8611);

        set_level(45);
        set_value(24000);
        set_max_lasting(7399);
        set("cp", 0);
        set("pp", 40);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Toàn Phong Hạng Liên";
}
