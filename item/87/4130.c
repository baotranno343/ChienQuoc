
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Toàn Phong yêu Đới");
        set_picid_1(8707);
        set_picid_2(8707);

        set_level(130);
        set_value(10000);
        set_max_lasting(16099);
        set("dp", 120);
        set("pp", 120);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Toàn Phong yêu Đới";
}
