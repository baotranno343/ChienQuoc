
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Phi Vân Quán");
        set_picid_1(6558);
        set_picid_2(6558);

        set_level(65);
        set_value(19000);
        set_max_lasting(11499);
        set("dp", 77);
        set("pp", 42);

        setup();

        set_gender(1);
        set_head_code(45);
}

// 函数：获取描述
string get_desc()
{
        return "Phi Vân Quán";
}
