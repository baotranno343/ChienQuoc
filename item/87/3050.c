
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Chiến Thiên Yêu Đới");
        set_picid_1(8710);
        set_picid_2(8710);

        set_level(50);
        set_value(10000);
        set_max_lasting(9399);
        set("dp", 48);
        set("pp", 35);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Chiến Thiên Yêu Đới";
}
