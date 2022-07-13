
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Tàn Dương Quán");
        set_picid_1(6542);
        set_picid_2(6542);

        set_level(110);
        set_value(36500);
        set_max_lasting(17499);
        set("dp", 126);
        set("pp", 69);

        setup();

        set_gender(1);
        set_head_code(48);
}

// 函数：获取描述
string get_desc()
{
        return "Tàn Dương Quán";
}
