
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Huyền Mộc Hạng Liên");
        set_picid_1(8608);
        set_picid_2(8608);

        set_level(65);
        set_value(38000);
        set_max_lasting(7999);
        set("cp", 0);
        set("pp", 60);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Huyền Mộc Hạng Liên";
}
