
// 自动生成：/make/equip/60b

#include <equip.h>

inherit ARMOR;

// 函数：适用门派
int get_family() { return %d; }

// 函数：构造处理
void create()
{
        set_name("%s");
        set_picid_1(%d);
        set_picid_2(%d);

        set_level(%d);
        set_value(%d);
        set_max_lasting(%d);
        set("dp", %d);
        set("pp", %d);

        setup();

        set_gender(%d);
        set_armor_code(%d);
}

// 函数：获取描述
string get_desc()
{
        return "%s";
}
