
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Phá Địch Đầu Cân");
        set_picid_1(6613);
        set_picid_2(6613);

        set_level(40);
        set_value(8500);
        set_max_lasting(7899);
        set("dp", 56);
        set("pp", 22);

        setup();

        set_gender(2);
        set_head_code(53);
}

// 函数：获取描述
string get_desc()
{
        return "Phá Địch Đầu Cân";
}
