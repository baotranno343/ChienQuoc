
// 自动生成：/make/equip/60b

#include <equip.h>

inherit NECK;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Vũ Hoàn Liên");
        set_picid_1(8664);
        set_picid_2(8664);

        set_level(80);
        set_value(53750);
        set_max_lasting(7299);
        set("cp", 0);
        set("pp", 82);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Vũ Hoàn Liên";
}
