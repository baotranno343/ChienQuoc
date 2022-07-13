
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Lý Ngư Đầu Cân");
        set_picid_1(6613);
        set_picid_2(6613);

        set_level(40);
        set_value(9000);
        set_max_lasting(6699);
        set("dp", 37);
        set("pp", 27);

        setup();

        set_gender(2);
        set_head_code(53);
}

// 函数：获取描述
string get_desc()
{
        return "Lý Ngư Đầu Cân";
}
