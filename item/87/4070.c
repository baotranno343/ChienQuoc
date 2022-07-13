
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Thiên Uy Yêu Đới");
        set_picid_1(8712);
        set_picid_2(8712);

        set_level(70);
        set_value(14900);
        set_max_lasting(9099);
        set("dp", 60);
        set("pp", 60);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Thiên Uy Yêu Đới";
}
