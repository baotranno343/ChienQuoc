
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 5; }

// 函数：构造处理
void create()
{
        set_name("Hạnh Phong Cân Mão");
        set_picid_1(6625);
        set_picid_2(6625);

        set_level(55);
        set_value(20700);
        set_max_lasting(6999);
        set("dp", 41);
        set("pp", 64);

        setup();

        set_gender(2);
        set_head_code(54);
}

// 函数：获取描述
string get_desc()
{
        return "Hạnh Phong Cân Mão";
}
