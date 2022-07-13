
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 3; }

// 函数：构造处理
void create()
{
        set_name("Hỗn Thiên Chiến Hài");
        set_picid_1(8812);
        set_picid_2(8812);

        set_level(70);
        set_value(15300);
        set_max_lasting(9699);
        set("dp", 34);
        set("sp", 34);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Hỗn Thiên Chiến Hài";
}
