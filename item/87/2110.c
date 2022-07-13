
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Tử Vân Yêu Đới");
        set_picid_1(8709);
        set_picid_2(8709);

        set_level(110);
        set_value(25000);
        set_max_lasting(14799);
        set("dp", 113);
        set("pp", 98);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Tử Vân Yêu Đới";
}
