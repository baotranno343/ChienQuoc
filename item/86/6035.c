
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 6; }

// 函数：构造处理
void create()
{
        set_name("Linh Hồn Hạng Liên");
        set_picid_1(8603);
        set_picid_2(8603);

        set_level(35);
        set_value(21500);
        set_max_lasting(5099);
        set("cp", 60);
        set("pp", 40);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Linh Hồn Hạng Liên";
}
