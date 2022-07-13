
// 自动生成：/make/equip/60b

#include <equip.h>

inherit BOOTS;

// 函数：适用门派
int get_family() { return 8; }

// 函数：构造处理
void create()
{
        set_name("Đằng Mạn Hài");
        set_picid_1(8800);
        set_picid_2(8800);

        set_level(5);
        set_value(900);
        set_max_lasting(3699);
        set("dp", 3);
        set("sp", 2);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Đằng Mạn Hài";
}
