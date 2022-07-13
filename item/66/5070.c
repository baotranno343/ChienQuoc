
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 5; }

// 函数：构造处理
void create()
{
        set_name("Thị Thiên Cân Mão");
        set_picid_1(6654);
        set_picid_2(6654);

        set_level(70);
        set_value(29000);
        set_max_lasting(7899);
        set("dp", 50);
        set("pp", 80);

        setup();

        set_gender(2);
        set_head_code(55);
}

// 函数：获取描述
string get_desc()
{
        return "Thị Thiên Cân Mão";
}
