
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 7; }

// 函数：构造处理
void create()
{
        set_name("Cổ Giáp Đầu Cân");
        set_picid_1(6600);
        set_picid_2(6600);

        set_level(20);
        set_value(1600);
        set_max_lasting(4899);
        set("dp", 19);
        set("pp", 27);

        setup();

        set_gender(2);
        set_head_code(51);
}

// 函数：获取描述
string get_desc()
{
        return "Cổ Giáp Đầu Cân";
}
