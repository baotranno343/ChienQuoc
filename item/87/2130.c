
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Ngọc Phong Yêu Đới");
        set_picid_1(8712);
        set_picid_2(8712);

        set_level(130);
        set_value(10000);
        set_max_lasting(16099);
        set("dp", 133);
        set("pp", 118);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Ngọc Phong Yêu Đới";
}
