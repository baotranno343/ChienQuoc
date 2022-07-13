
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 4; }

// 函数：构造处理
void create()
{
        set_name("Hiên Duyên Yêu Đới");
        set_picid_1(8712);
        set_picid_2(8712);

        set_level(110);
        set_value(24100);
        set_max_lasting(11499);
        set("dp", 100);
        set("pp", 100);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Hiên Duyên Yêu Đới";
}
