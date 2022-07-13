
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 5; }

// 函数：构造处理
void create()
{
        set_name("Trảm Hầu Quán");
        set_picid_1(6540);
        set_picid_2(6540);

        set_level(80);
        set_value(34500);
        set_max_lasting(8499);
        set("dp", 56);
        set("pp", 91);

        setup();

        set_gender(1);
        set_head_code(46);
}

// 函数：获取描述
string get_desc()
{
        return "Trảm Hầu Quán";
}
