
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Thanh Vân Đầu Cân");
        set_picid_1(6610);
        set_picid_2(6610);

        set_level(25);
        set_value(4500);
        set_max_lasting(5799);
        set("dp", 25);
        set("pp", 18);

        setup();

        set_gender(2);
        set_head_code(51);
}

// 函数：获取描述
string get_desc()
{
        return "Thanh Vân Đầu Cân";
}
