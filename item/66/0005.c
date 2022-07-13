
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 8; }

// 函数：构造处理
void create()
{
        set_name("Ma Bố Mão");
        set_picid_1(6610);
        set_picid_2(6610);

        set_level(5);
        set_value(1350);
        set_max_lasting(3699);
        set("dp", 8);
        set("pp", 0);

        setup();

        set_gender(2);
        set_head_code(50);
}

// 函数：获取描述
string get_desc()
{
        return "Ma Bố Mão";
}
