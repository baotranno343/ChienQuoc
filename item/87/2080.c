
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 2; }

// 函数：构造处理
void create()
{
        set_name("Phiên Vân Yêu Đới");
        set_picid_1(8710);
        set_picid_2(8710);

        set_level(80);
        set_value(17500);
        set_max_lasting(12099);
        set("dp", 83);
        set("pp", 68);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Phiên Vân Yêu Đới";
}
