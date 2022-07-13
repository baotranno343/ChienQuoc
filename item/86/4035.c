
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Nguyệt Quang Hạng Liên");
        set_picid_1(8600);
        set_picid_2(8600);

        set_level(35);
        set_value(18900);
        set_max_lasting(5899);
        set("cp", 0);
        set("pp", 37);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Nguyệt Quang Hạng Liên";
}
