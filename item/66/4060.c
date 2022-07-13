
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Kim Ty Cân Mão");
        set_picid_1(6605);
        set_picid_2(6605);

        set_level(60);
        set_value(15000);
        set_max_lasting(7899);
        set("dp", 53);
        set("pp", 39);

        setup();

        set_gender(2);
        set_head_code(54);
}

// 函数：获取描述
string get_desc()
{
        return "Kim Ty Cân Mão";
}
