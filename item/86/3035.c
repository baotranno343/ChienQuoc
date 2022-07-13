
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Lưu Vân Hạng Liên");
        set_picid_1(8606);
        set_picid_2(8606);

        set_level(35);
        set_value(17000);
        set_max_lasting(7099);
        set("cp", 0);
        set("pp", 30);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Lưu Vân Hạng Liên";
}
