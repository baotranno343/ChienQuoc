
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Chiến Thần Khôi");
        set_picid_1(6582);
        set_picid_2(6582);

        set_level(120);
        set_value(40000);
        set_max_lasting(18699);
        set("dp", 152);
        set("pp", 70);

        setup();

        set_gender(1);
        set_head_code(48);
}

// 函数：获取描述
string get_desc()
{
        return "Chiến Thần Khôi";
}
