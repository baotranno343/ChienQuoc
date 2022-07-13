
// 自动生成：/make/equip/60b

#include <equip.h>

inherit WAIST;

// 函数：适用门派
int get_family() { return 7; }

// 函数：构造处理
void create()
{
        set_name("Sí Văn Yêu Đới");
        set_picid_1(8707);
        set_picid_2(8707);

        set_level(100);
        set_value(32500);
        set_max_lasting(7699);
        set("dp", 88);
        set("pp", 102);

        setup();
}

// 函数：获取描述
string get_desc()
{
        return "Sí Văn Yêu Đới";
}
