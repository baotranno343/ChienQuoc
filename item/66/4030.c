
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Thiên Thuỷ Đầu Cân");
        set_picid_1(6620);
        set_picid_2(6620);

        set_level(30);
        set_value(6000);
        set_max_lasting(6099);
        set("dp", 29);
        set("pp", 21);

        setup();

        set_gender(2);
        set_head_code(52);
}

// 函数：获取描述
string get_desc()
{
        return "Thiên Thuỷ Đầu Cân";
}
