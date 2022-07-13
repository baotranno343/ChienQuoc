
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Kim Ty Yêu Đới");
        set_picid_1(8714);
        set_picid_2(8714);

        set_level(60);
        set_value(12600);
        set_max_lasting(8499);
        set("dp", 50);
        set("pp", 50);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Kim Ty Yêu Đới";
}
