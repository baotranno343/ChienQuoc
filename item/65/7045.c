
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 7; }

// 函数：构造处理
void create()
{
        set_name("Thương Côn Quán");
        set_picid_1(6576);
        set_picid_2(6576);

        set_level(45);
        set_value(15300);
        set_max_lasting(6399);
        set("dp", 34);
        set("pp", 52);

        setup();

        set_gender(1);
        set_head_code(43);
}

// 函数：获取描述
string get_desc()
{
        return "Thương Côn Quán";
}
