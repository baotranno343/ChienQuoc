
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 7; }

// 函数：构造处理
void create()
{
        set_name("Hồn Sương Quán");
        set_picid_1(6536);
        set_picid_2(6536);

        set_level(40);
        set_value(12500);
        set_max_lasting(6099);
        set("dp", 31);
        set("pp", 47);

        setup();

        set_gender(1);
        set_head_code(43);
}

// 函数：获取描述
string get_desc()
{
        return "Hồn Sương Quán";
}
