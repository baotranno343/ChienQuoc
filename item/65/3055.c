
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Phi Báo Quán");
        set_picid_1(6538);
        set_picid_2(6538);

        set_level(55);
        set_value(13700);
        set_max_lasting(9699);
        set("dp", 74);
        set("pp", 31);

        setup();

        set_gender(1);
        set_head_code(44);
}

// 函数：获取描述
string get_desc()
{
        return "Phi Báo Quán";
}
