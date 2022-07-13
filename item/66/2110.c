
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Tử Vân Hà Quán");
        set_picid_1(6680);
        set_picid_2(6680);

        set_level(110);
        set_value(36500);
        set_max_lasting(17499);
        set("dp", 126);
        set("pp", 72);

        setup();

        set_gender(2);
        set_head_code(58);
}

// 函数：获取描述
string get_desc()
{
        return "Tử Vân Hà Quán";
}
