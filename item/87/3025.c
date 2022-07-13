
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Chiến Không Yêu Đới");
        set_picid_1(8708);
        set_picid_2(8708);

        set_level(25);
        set_value(3750);
        set_max_lasting(7099);
        set("dp", 23);
        set("pp", 10);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Chiến Không Yêu Đới";
}
