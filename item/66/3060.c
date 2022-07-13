
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Chiến Tướng Cân Mão");
        set_picid_1(6605);
        set_picid_2(6605);

        set_level(60);
        set_value(15500);
        set_max_lasting(10299);
        set("dp", 80);
        set("pp", 34);

        setup();

        set_gender(2);
        set_head_code(54);
}

// 函数：获取描述
string get_desc()
{
        return "Chiến Tướng Cân Mão";
}
