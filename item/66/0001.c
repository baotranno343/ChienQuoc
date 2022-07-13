
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

//int get_item_color() { return 1; }
// 函数：适用门派
int get_family() { return 8; }

// 函数：构造处理
void create()
{
        set_name("Bố Mão");
        set_picid_1(6610);
        set_picid_2(6610);

        set_level(0);
        set_value(400);
        set_max_lasting(2499);
        set("dp", 5);
        set("pp", 0);

        setup();

        set_gender(2);
        set_head_code(50);
}

// 函数：获取描述
string get_desc()
{
        return "Bố Mão";
}
