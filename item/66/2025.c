
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Phất Hiểu Đầu Cân");
        set_picid_1(6610);
        set_picid_2(6610);

        set_level(25);
        set_value(3300);
        set_max_lasting(6099);
        set("dp", 32);
        set("pp", 21);

        setup();

        set_gender(2);
        set_head_code(51);
}

// 函数：获取描述
string get_desc()
{
        return "Phất Hiểu Đầu Cân";
}
