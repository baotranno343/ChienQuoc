
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Phi Thiên Cân Mão");
        set_picid_1(6625);
        set_picid_2(6625);

        set_level(55);
        set_value(13700);
        set_max_lasting(9699);
        set("dp", 66);
        set("pp", 39);

        setup();

        set_gender(2);
        set_head_code(54);
}

// 函数：获取描述
string get_desc()
{
        return "Phi Thiên Cân Mão";
}
