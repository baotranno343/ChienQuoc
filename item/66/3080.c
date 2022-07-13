
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Vân Long Cân Mão");
        set_picid_1(6638);
        set_picid_2(6638);

        set_level(80);
        set_value(26000);
        set_max_lasting(13899);
        set("dp", 104);
        set("pp", 46);

        setup();

        set_gender(2);
        set_head_code(56);
}

// 函数：获取描述
string get_desc()
{
        return "Vân Long Cân Mão";
}
