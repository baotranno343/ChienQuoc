
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 5; }

// 函数：构造处理
void create()
{
        set_name("Hoả Phượng Hạng Liên");
        set_picid_1(8655);
        set_picid_2(8655);

        set_level(35);
        set_value(21500);
        set_max_lasting(5099);
        set("cp", 58);
        set("pp", 41);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Hoả Phượng Hạng Liên";
}
