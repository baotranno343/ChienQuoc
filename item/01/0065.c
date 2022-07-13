
#include <equip.h>

inherit HEAD;

// 函数：构造处理
void create()
{
        set_name("麟甲战盔");
        set_picid_1(6542);
        set_picid_2(6542);
        set_unit("顶");

        set_level(0);
        set_value(0);
        set_max_lasting(1099);
        set("dp", 10);
        set("pp", 8);

        setup();

        set_gender(1);
        set_head_code(M_ZHANKUI);
        set_head_color(0x49c25880);
}

// 函数：获取描述
string get_desc()
{
        return "麟甲战盔";
}
