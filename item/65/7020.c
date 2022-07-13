
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 7; }

// 函数：构造处理
void create()
{
        set_name("Cổ Giáp Mão");
        set_picid_1(6554);
        set_picid_2(6554);

        set_level(20);
        set_value(1600);
        set_max_lasting(4899);
        set("dp", 19);
        set("pp", 27);

        setup();

        set_gender(1);
        set_head_code(41);
}

// 函数：获取描述
string get_desc()
{
        return "Cổ Giáp Mão";
}
