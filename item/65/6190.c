
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 6; }

// 函数：构造处理
void create()
{
        set_name("Phi Thiên Vũ Mão");
        set_picid_1(6600);
        set_picid_2(6600);

        set_level(100);
        set_value(10000);
        set_max_lasting(16099);
        set("dp", 83);
        set("pp", 146);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Phi Thiên Vũ Mão";
}
