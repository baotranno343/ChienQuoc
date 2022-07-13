
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Sinh Mệnh Hạng Liên");
        set_picid_1(8650);
        set_picid_2(8650);

        set_level(35);
        set_value(17000);
        set_max_lasting(7099);
        set("cp", 0);
        set("pp", 40);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Sinh Mệnh Hạng Liên";
}
