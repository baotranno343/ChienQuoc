
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Định Hồn Hạng Liên");
        set_picid_1(8662);
        set_picid_2(8662);

        set_level(90);
        set_value(61500);
        set_max_lasting(7599);
        set("cp", 0);
        set("pp", 92);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Định Hồn Hạng Liên";
}
