
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 7; }

// 函数：构造处理
void create()
{
        set_name("Chiếu Thế Lý");
        set_picid_1(8810);
        set_picid_2(8810);

        set_level(55);
        set_value(12700);
        set_max_lasting(6299);
        set("dp", 13);
        set("sp", 21);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Chiếu Thế Lý";
}
