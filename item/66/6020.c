
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 6; }

// 函数：构造处理
void create()
{
        set_name("Tế Ma Đầu Cân");
        set_picid_1(6600);
        set_picid_2(6600);

        set_level(20);
        set_value(1600);
        set_max_lasting(4899);
        set("dp", 17);
        set("pp", 25);

        setup();

        set_gender(2);
        set_head_code(51);
}

// 函数：获取描述
string get_desc()
{
        return "Tế Ma Đầu Cân";
}
