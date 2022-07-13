
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 7; }

// 函数：构造处理
void create()
{
        set_name("Tương Thiết Đầu Cân");
        set_picid_1(6610);
        set_picid_2(6610);

        set_level(25);
        set_value(4300);
        set_max_lasting(5199);
        set("dp", 22);
        set("pp", 32);

        setup();

        set_gender(2);
        set_head_code(51);
}

// 函数：获取描述
string get_desc()
{
        return "Tương Thiết Đầu Cân";
}
