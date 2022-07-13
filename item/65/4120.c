
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Thiên Thần Quán");
        set_picid_1(6582);
        set_picid_2(6582);

        set_level(120);
        set_value(33000);
        set_max_lasting(11499);
        set("dp", 101);
        set("pp", 75);

        setup();

        set_gender(1);
        set_head_code(48);
}

// 函数：获取描述
string get_desc()
{
        return "Thiên Thần Quán";
}
