
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 5; }

// 函数：构造处理
void create()
{
        set_name("Khâm Thiên Hà Quán");
        set_picid_1(6682);
        set_picid_2(6682);

        set_level(120);
        set_value(56500);
        set_max_lasting(10899);
        set("dp", 80);
        set("pp", 135);

        setup();

        set_gender(2);
        set_head_code(58);
}

// 函数：获取描述
string get_desc()
{
        return "Khâm Thiên Hà Quán";
}
