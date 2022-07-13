
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 5; }

// 函数：构造处理
void create()
{
        set_name("Ngự Phách Bì Mão");
        set_picid_1(6500);
        set_picid_2(6500);

        set_level(130);
        set_value(10000);
        set_max_lasting(16099);
        set("dp", 86);
        set("pp", 146);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Ngự Phác Bì Mão";
}
