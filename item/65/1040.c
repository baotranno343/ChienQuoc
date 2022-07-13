
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Lục Thanh Mão");
        set_picid_1(6536);
        set_picid_2(6536);

        set_level(40);
        set_value(8500);
        set_max_lasting(7899);
        set("dp", 49);
        set("pp", 27);

        setup();

        set_gender(1);
        set_head_code(43);
}

// 函数：获取描述
string get_desc()
{
        return "Lục Thanh Mão";
}
