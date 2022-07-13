
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 1; }

// 函数：构造处理
void create()
{
        set_name("Truy Phong Cân Mão");
        set_picid_1(6623);
        set_picid_2(6623);

        set_level(45);
        set_value(10300);
        set_max_lasting(8499);
        set("dp", 55);
        set("pp", 30);

        setup();

        set_gender(2);
        set_head_code(53);
}

// 函数：获取描述
string get_desc()
{
        return "Truy Phong Cân Mão";
}
