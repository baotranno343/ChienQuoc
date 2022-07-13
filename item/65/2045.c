
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Phi Hổ Quán");
        set_picid_1(6576);
        set_picid_2(6576);

        set_level(45);
        set_value(10300);
        set_max_lasting(8499);
        set("dp", 55);
        set("pp", 33);

        setup();

        set_gender(1);
        set_head_code(43);
}

// 函数：获取描述
string get_desc()
{
        return "Phi Hổ Quán";
}
