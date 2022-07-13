
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Cuồng Chiến Yêu Đới");
        set_picid_1(8708);
        set_picid_2(8708);

        set_level(30);
        set_value(5000);
        set_max_lasting(7599);
        set("dp", 28);
        set("pp", 15);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Cuồng Chiến Yêu Đới";
}
