
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Kì Lân Mão");
        set_picid_1(6560);
        set_picid_2(6560);

        set_level(90);
        set_value(29500);
        set_max_lasting(15099);
        set("dp", 104);
        set("pp", 57);

        setup();

        set_gender(1);
        set_head_code(46);
}

// 函数：获取描述
string get_desc()
{
        return "Kì Lân Mão";
}
