
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 7; }

// 函数：构造处理
void create()
{
        set_name("Hồn Sương Lý");
        set_picid_1(8810);
        set_picid_2(8810);

        set_level(40);
        set_value(7500);
        set_max_lasting(5599);
        set("dp", 10);
        set("sp", 15);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Hồn Sương Lý";
}
