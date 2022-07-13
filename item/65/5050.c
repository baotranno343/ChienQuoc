
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 5; }

// 函数：构造处理
void create()
{
        set_name("Dực Phi Quán");
        set_picid_1(6578);
        set_picid_2(6578);

        set_level(50);
        set_value(18000);
        set_max_lasting(6699);
        set("dp", 38);
        set("pp", 58);

        setup();

        set_gender(1);
        set_head_code(43);
}

// 函数：获取描述
string get_desc()
{
        return "Dực Phi Quán";
}
