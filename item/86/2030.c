
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Mệnh Vân Hạng Liên");
        set_picid_1(8650);
        set_picid_2(8650);

        set_level(30);
        set_value(13500);
        set_max_lasting(6999);
        set("cp", 0);
        set("pp", 35);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Mệnh Vân Hạng Liên";
}
