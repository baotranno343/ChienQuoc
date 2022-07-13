
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Phi Vân Cân Mão");
        set_picid_1(6634);
        set_picid_2(6634);

        set_level(65);
        set_value(19000);
        set_max_lasting(11499);
        set("dp", 77);
        set("pp", 42);

        setup();

        set_gender(2);
        set_head_code(55);
}

// 函数：获取描述
string get_desc()
{
        return "Phi Vân Cân Mão";
}
