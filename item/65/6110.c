
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 6; }

// 函数：构造处理
void create()
{
        set_name("Can Vân Quán");
        set_picid_1(6542);
        set_picid_2(6542);

        set_level(110);
        set_value(51000);
        set_max_lasting(10299);
        set("dp", 71);
        set("pp", 124);

        setup();

        set_gender(1);
        set_head_code(48);
}

// 函数：获取描述
string get_desc()
{
        return "Can Vân Quán";
}
