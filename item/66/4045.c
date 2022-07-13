
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Truy Vân Cân Mão");
        set_picid_1(6623);
        set_picid_2(6623);

        set_level(45);
        set_value(10500);
        set_max_lasting(6999);
        set("dp", 41);
        set("pp", 30);

        setup();

        set_gender(2);
        set_head_code(53);
}

// 函数：获取描述
string get_desc()
{
        return "Truy Vân Cân Mão";
}
