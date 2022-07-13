
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Thiên Uy Cân Mão");
        set_picid_1(6654);
        set_picid_2(6654);

        set_level(70);
        set_value(18000);
        set_max_lasting(8499);
        set("dp", 61);
        set("pp", 45);

        setup();

        set_gender(2);
        set_head_code(55);
}

// 函数：获取描述
string get_desc()
{
        return "Thiên Uy Cân Mão";
}
