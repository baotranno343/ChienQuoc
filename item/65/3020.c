
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Sa Trường Mão");
        set_picid_1(6554);
        set_picid_2(6554);

        set_level(20);
        set_value(1600);
        set_max_lasting(5499);
        set("dp", 32);
        set("pp", 10);

        setup();

        set_gender(1);
        set_head_code(41);
}

// 函数：获取描述
string get_desc()
{
        return "Sa Trường Mão";
}
