
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Vĩnh Hằng Hạng Liên");
        set_picid_1(8660);
        set_picid_2(8660);

        set_level(70);
        set_value(46000);
        set_max_lasting(6999);
        set("cp", 0);
        set("pp", 72);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Vĩnh Hằng Hạng Liên";
}
