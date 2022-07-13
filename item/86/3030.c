
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Huyền Minh Hạng Liên");
        set_picid_1(8603);
        set_picid_2(8603);

        set_level(30);
        set_value(13500);
        set_max_lasting(6999);
        set("cp", 0);
        set("pp", 25);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Huyền Minh Hạng Liên";
}
