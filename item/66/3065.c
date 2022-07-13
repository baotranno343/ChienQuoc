
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Chiến Long Cân Mão");
        set_picid_1(6634);
        set_picid_2(6634);

        set_level(65);
        set_value(19000);
        set_max_lasting(11499);
        set("dp", 86);
        set("pp", 37);

        setup();

        set_gender(2);
        set_head_code(55);
}

// 函数：获取描述
string get_desc()
{
        return "Chiến Long Cân Mão";
}
