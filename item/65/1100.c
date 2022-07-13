
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Long Lân Quán");
        set_picid_1(6580);
        set_picid_2(6580);

        set_level(100);
        set_value(33000);
        set_max_lasting(16299);
        set("dp", 115);
        set("pp", 63);

        setup();

        set_gender(1);
        set_head_code(47);
}

// 函数：获取描述
string get_desc()
{
        return "Long Lân Quán";
}
