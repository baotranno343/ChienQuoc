
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 6; }

// 函数：构造处理
void create()
{
        set_name("Phi Ngọc Cân Mão");
        set_picid_1(6634);
        set_picid_2(6634);

        set_level(65);
        set_value(26300);
        set_max_lasting(7599);
        set("dp", 44);
        set("pp", 75);

        setup();

        set_gender(2);
        set_head_code(55);
}

// 函数：获取描述
string get_desc()
{
        return "Phi Ngọc Cân Mão";
}
