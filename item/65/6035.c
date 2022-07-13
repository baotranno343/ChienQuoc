
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 6; }

// 函数：构造处理
void create()
{
        set_name("Bạch Hổ Mão");
        set_picid_1(6556);
        set_picid_2(6556);

        set_level(35);
        set_value(9700);
        set_max_lasting(5799);
        set("dp", 26);
        set("pp", 42);

        setup();

        set_gender(1);
        set_head_code(42);
}

// 函数：获取描述
string get_desc()
{
        return "Bạch Hổ Mão";
}
