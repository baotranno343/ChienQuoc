
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Long Bì Mão");
        set_picid_1(6558);
        set_picid_2(6558);

        set_level(65);
        set_value(16500);
        set_max_lasting(8199);
        set("dp", 57);
        set("pp", 42);

        setup();

        set_gender(1);
        set_head_code(45);
}

// 函数：获取描述
string get_desc()
{
        return "Long Bì Mão";
}
