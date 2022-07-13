
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Nhiếp Hồn Lý");
        set_picid_1(8810);
        set_picid_2(8810);

        set_level(100);
        set_value(21000);
        set_max_lasting(12399);
        set("dp", 22);
        set("sp", 106);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Nhiếp Hồn Lý";
}
