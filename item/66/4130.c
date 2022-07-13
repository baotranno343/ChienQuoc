
// 自动生成：/make/equip/60b

#include <equip.h>

inherit HEAD;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Toàn Phong Đầu Cân");
        set_picid_1(8714);
        set_picid_2(8714);

        set_level(130);
        set_value(10000);
        set_max_lasting(16099);
        set("dp", 109);
        set("pp", 81);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Toàn Phong Đầu Cân";
}
