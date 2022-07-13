
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Sa Trường Yêu Đới");
        set_picid_1(8707);
        set_picid_2(8707);

        set_level(20);
        set_value(2500);
        set_max_lasting(6699);
        set("dp", 18);
        set("pp", 5);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Sa Trường Yêu Đới";
}
