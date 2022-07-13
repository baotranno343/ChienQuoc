
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 6; }

// 函数：构造处理
void create()
{
        set_name("Thuỳ Vân Mão");
        set_picid_1(6558);
        set_picid_2(6558);

        set_level(60);
        set_value(23500);
        set_max_lasting(7299);
        set("dp", 41);
        set("pp", 69);

        setup();

        set_gender(1);
        set_head_code(44);
}

// 函数：获取描述
string get_desc()
{
        return "Thuỳ Vân Mão";
}
