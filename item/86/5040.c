
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 5; }

// 函数：构造处理
void create()
{
        set_name("Khỉ Lệ Hạng Liên");
        set_picid_1(8650);
        set_picid_2(8650);

        set_level(40);
        set_value(26000);
        set_max_lasting(5199);
        set("cp", 68);
        set("pp", 46);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Khỉ Lệ Hạng Liên";
}
